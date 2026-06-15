#ifndef CLIPBOARDBRIDGE_H
#define CLIPBOARDBRIDGE_H

#include <QObject>

class QString;
class QWebEngineView;

class ClipboardBridge : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardBridge(QObject* parent = nullptr);

    // Wires a ClipboardBridge + QWebChannel into view's page so that
    // navigator.clipboard.writeText() and copy events forward to the
    // native Qt clipboard. Both objects are parented to view.
    static void install(QWebEngineView* view);

public slots:
    void copyToClipboard(const QString& text);
};

#endif // CLIPBOARDBRIDGE_H
