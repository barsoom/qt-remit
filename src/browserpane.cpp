#include "browserpane.h"

#include "findbaricons.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QSize>
#include <QResizeEvent>
#include <QShortcut>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWebEngineFindTextResult>
#include <QWebEnginePage>
#include <QWebEngineView>

BrowserPane::BrowserPane(QWebEngineView* view, Style style, QWidget* parent)
    : QWidget(parent), m_view(view)
{
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    if (style == Style::NavButtons) {
        auto* toolbar = new QWidget(this);
        auto* tl = new QHBoxLayout(toolbar);
        tl->setContentsMargins(4, 2, 4, 2);
        tl->setSpacing(2);

        auto* backBtn = new QToolButton;
        backBtn->setDefaultAction(m_view->pageAction(QWebEnginePage::Back));
        auto* forwardBtn = new QToolButton;
        forwardBtn->setDefaultAction(m_view->pageAction(QWebEnginePage::Forward));
        auto* reloadBtn = new QToolButton;
        reloadBtn->setDefaultAction(m_view->pageAction(QWebEnginePage::Reload));

        connect(m_view, &QWebEngineView::loadStarted, this, [=]() {
            reloadBtn->setDefaultAction(m_view->pageAction(QWebEnginePage::Stop));
        });
        connect(m_view, &QWebEngineView::loadFinished, this, [=](bool) {
            reloadBtn->setDefaultAction(m_view->pageAction(QWebEnginePage::Reload));
        });

        tl->addWidget(backBtn);
        tl->addWidget(forwardBtn);
        tl->addWidget(reloadBtn);
        tl->addStretch();
        layout->addWidget(toolbar);
    }

    m_progressBar = new QProgressBar(this);
    m_progressBar->setFixedHeight(3);
    m_progressBar->setTextVisible(false);
    m_progressBar->setRange(0, 100);
    m_progressBar->setStyleSheet(
        "QProgressBar { border: none; background: transparent; }"
        "QProgressBar::chunk { background-color: #4285F4; }"
    );
    m_progressBar->hide();

    connect(m_view, &QWebEngineView::loadStarted, this, [this]() {
        m_progressBar->setValue(0);
        updateProgressBarGeometry();
        m_progressBar->show();
        m_progressBar->raise();
    });
    connect(m_view, &QWebEngineView::loadProgress, m_progressBar, &QProgressBar::setValue);
    connect(m_view, &QWebEngineView::loadFinished, this, [this](bool) {
        m_progressBar->hide();
    });

    layout->addWidget(m_view, 1);

    // Find bar (hidden by default, shown with Ctrl+F)
    m_findBar = new QWidget(this);
    m_findBar->setObjectName("findBar");
    m_findBar->setStyleSheet(
        "#findBar { background: palette(window); "
        "border-top: 1px solid palette(mid); } "
        "#findBar QToolButton { "
        "  border: none; background: transparent; "
        "  padding: 2px 6px; border-radius: 3px; "
        "} "
        "#findBar QToolButton:hover { background: palette(midlight); } "
        "#findBar QToolButton:pressed { background: palette(mid); }"
    );
    auto* fl = new QHBoxLayout(m_findBar);
    fl->setContentsMargins(8, 4, 6, 4);
    fl->setSpacing(2);

    m_findInput = new QLineEdit;
    m_findInput->setPlaceholderText("Find in page");
    m_findInput->setClearButtonEnabled(true);
    m_findInput->setMaximumWidth(280);

    auto makeFlatButton = [this](const QIcon& icon, const QString& tip) {
        auto* btn = new QToolButton;
        btn->setIcon(icon);
        btn->setToolTip(tip);
        btn->setAutoRaise(true);
        btn->setFocusPolicy(Qt::NoFocus);
        btn->setIconSize(QSize(14, 14));
        return btn;
    };

    const QPalette pal = palette();
    auto* prevBtn = makeFlatButton(FindBarIcons::chevronUp(pal),
                                   "Previous match (Shift+Enter)");
    auto* nextBtn = makeFlatButton(FindBarIcons::chevronDown(pal),
                                   "Next match (Enter)");
    auto* closeBtn = makeFlatButton(FindBarIcons::close(pal),
                                    "Close (Esc)");

    m_findCount = new QLabel;
    m_findCount->setMinimumWidth(60);
    {
        QPalette countPal = m_findCount->palette();
        countPal.setColor(QPalette::WindowText,
                          countPal.color(QPalette::Disabled, QPalette::WindowText));
        m_findCount->setPalette(countPal);
    }

    fl->addWidget(m_findInput);
    fl->addWidget(prevBtn);
    fl->addWidget(nextBtn);
    fl->addWidget(m_findCount);
    fl->addStretch();
    fl->addWidget(closeBtn);
    m_findBar->hide();
    layout->addWidget(m_findBar);

    connect(closeBtn, &QToolButton::clicked, this, &BrowserPane::hideFindBar);
    connect(prevBtn, &QToolButton::clicked, this, &BrowserPane::findBackward);
    connect(nextBtn, &QToolButton::clicked, this, &BrowserPane::findForward);
    connect(m_findInput, &QLineEdit::textChanged, this, [this](const QString& text) {
        if (text.isEmpty()) {
            m_view->findText({});
            m_findCount->clear();
        } else {
            findForward();
        }
    });
    connect(m_findInput, &QLineEdit::returnPressed, this, &BrowserPane::findForward);
    {
        auto* sc = new QShortcut(QKeySequence(Qt::SHIFT | Qt::Key_Return), m_findInput);
        sc->setContext(Qt::WidgetShortcut);
        connect(sc, &QShortcut::activated, this, &BrowserPane::findBackward);
    }

    // Keyboard shortcuts
    auto addShortcut = [this](const QKeySequence& key) {
        auto* sc = new QShortcut(key, this);
        sc->setContext(Qt::WidgetWithChildrenShortcut);
        return sc;
    };

    connect(addShortcut(QKeySequence::Find), &QShortcut::activated,
            this, &BrowserPane::showFindBar);
    connect(addShortcut(Qt::Key_Escape), &QShortcut::activated,
            this, [this]() { if (m_findBar->isVisible()) hideFindBar(); });
    connect(addShortcut(QKeySequence::Refresh), &QShortcut::activated,
            m_view, &QWebEngineView::reload);
    connect(addShortcut(QKeySequence(Qt::CTRL | Qt::Key_R)), &QShortcut::activated,
            m_view, &QWebEngineView::reload);
    connect(addShortcut(QKeySequence(Qt::SHIFT | Qt::Key_F5)), &QShortcut::activated,
            this, [this]() { m_view->page()->triggerAction(QWebEnginePage::ReloadAndBypassCache); });

    if (style == Style::NavButtons) {
        connect(addShortcut(QKeySequence::Back), &QShortcut::activated,
                this, [this]() { m_view->page()->triggerAction(QWebEnginePage::Back); });
        connect(addShortcut(QKeySequence::Forward), &QShortcut::activated,
                this, [this]() { m_view->page()->triggerAction(QWebEnginePage::Forward); });
    }
}

void BrowserPane::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateProgressBarGeometry();
}

void BrowserPane::updateProgressBarGeometry() {
    m_progressBar->setGeometry(0, m_view->y(), width(), 3);
}

void BrowserPane::showFindBar() {
    m_findBar->show();
    m_findInput->setFocus();
    m_findInput->selectAll();
}

void BrowserPane::hideFindBar() {
    m_findBar->hide();
    m_view->findText({});
    m_findInput->clear();
    m_findCount->clear();
}

void BrowserPane::findForward() {
    m_view->findText(m_findInput->text(), {}, [this](const QWebEngineFindTextResult& result) {
        if (result.numberOfMatches() == 0)
            m_findCount->setText("No results");
        else
            m_findCount->setText(QString("%1/%2").arg(result.activeMatch()).arg(result.numberOfMatches()));
    });
}

void BrowserPane::findBackward() {
    m_view->findText(m_findInput->text(), QWebEnginePage::FindBackward,
                     [this](const QWebEngineFindTextResult& result) {
        if (result.numberOfMatches() == 0)
            m_findCount->setText("No results");
        else
            m_findCount->setText(QString("%1/%2").arg(result.activeMatch()).arg(result.numberOfMatches()));
    });
}
