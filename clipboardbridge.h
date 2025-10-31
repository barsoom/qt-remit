#ifndef CLIPBOARDBRIDGE_H
#define CLIPBOARDBRIDGE_H

#include <QObject>

class QString;

class ClipboardBridge : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardBridge(QObject* parent = nullptr);

public slots:
    void copyToClipboard(const QString& text);
};

#endif // CLIPBOARDBRIDGE_H
