#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

class QLineEdit;

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget* parent = nullptr);

    QString remitUrl() const;
    QString authToken() const;

private:
    QLineEdit* urlLineEdit;
    QLineEdit* tokenLineEdit;
};

#endif // SETTINGSDIALOG_H
