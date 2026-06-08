#ifndef BROWSERPANE_H
#define BROWSERPANE_H

#include <QWidget>

class QResizeEvent;
class QWebEngineView;
class QProgressBar;
class QLineEdit;
class QLabel;

class BrowserPane : public QWidget {
    Q_OBJECT
public:
    enum class Style { ProgressOnly, NavButtons };
    BrowserPane(QWebEngineView* view, Style style, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QWebEngineView* m_view;
    QProgressBar* m_progressBar = nullptr;
    QWidget* m_findBar = nullptr;
    QLineEdit* m_findInput = nullptr;
    QLabel* m_findCount = nullptr;

    void updateProgressBarGeometry();
    void showFindBar();
    void hideFindBar();
    void findForward();
    void findBackward();
};

#endif // BROWSERPANE_H
