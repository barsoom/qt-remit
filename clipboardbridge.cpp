#include <QApplication>
#include <QClipboard>
#include <QString>

#include "clipboardbridge.h"

ClipboardBridge::ClipboardBridge(QObject* parent) : QObject(parent)
{
}

void ClipboardBridge::copyToClipboard(const QString& text)
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(text);
}
