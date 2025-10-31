#include <QApplication>
#include <QUrl>

#include "mainwindow.h"
#include "settings.h"
#include "settingsdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Show settings dialog if not configured
    if (!Settings::isConfigured()) {
        SettingsDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            Settings::setRemitBaseUrl(dialog.remitUrl());
            Settings::setAuthToken(dialog.authToken());
        } else {
            // User cancelled, exit the application
            return 0;
        }
    }

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
