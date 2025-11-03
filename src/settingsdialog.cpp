#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QLabel>
#include <QFont>
#include <QPixmap>

#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Configure Remit");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Header with centered, larger text
    QLabel* instructions = new QLabel(
        "Welcome to qt-remit! Please configure your Remit instance:"
    );
    instructions->setWordWrap(true);
    instructions->setAlignment(Qt::AlignCenter);
    instructions->setContentsMargins(0, 0, 0, 10);
    QFont headerFont = instructions->font();
    headerFont.setPointSize(headerFont.pointSize() + 2);
    instructions->setFont(headerFont);
    mainLayout->addWidget(instructions);

    // Horizontal layout for icon and form
    QHBoxLayout* contentLayout = new QHBoxLayout();

    // Icon on the left
    QLabel* iconLabel = new QLabel(this);
    QPixmap icon(":/assets/qt-remit.png");
    if (!icon.isNull()) {
        iconLabel->setPixmap(icon.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    iconLabel->setContentsMargins(0, 0, 20, 0);
    contentLayout->addWidget(iconLabel);

    // Form layout
    QFormLayout* formLayout = new QFormLayout();

    urlLineEdit = new QLineEdit(this);
    urlLineEdit->setPlaceholderText("https://remit.example.com/");
    urlLineEdit->setMinimumWidth(350);
    formLayout->addRow("Remit URL:", urlLineEdit);

    tokenLineEdit = new QLineEdit(this);
    tokenLineEdit->setPlaceholderText("Your authentication token");
    tokenLineEdit->setEchoMode(QLineEdit::Password);
    tokenLineEdit->setMinimumWidth(350);
    formLayout->addRow("Auth Token:", tokenLineEdit);

    contentLayout->addLayout(formLayout);
    mainLayout->addLayout(contentLayout);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        this
    );
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    mainLayout->addWidget(buttonBox);

    setMinimumWidth(500);
}

QString SettingsDialog::remitUrl() const
{
    return urlLineEdit->text();
}

QString SettingsDialog::authToken() const
{
    return tokenLineEdit->text();
}
