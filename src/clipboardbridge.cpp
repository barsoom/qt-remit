#include <QApplication>
#include <QClipboard>
#include <QFile>
#include <QString>
#include <QWebChannel>
#include <QWebEnginePage>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QWebEngineView>

#include "clipboardbridge.h"

ClipboardBridge::ClipboardBridge(QObject* parent) : QObject(parent)
{
}

void ClipboardBridge::copyToClipboard(const QString& text)
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

void ClipboardBridge::install(QWebEngineView* view)
{
    auto* bridge = new ClipboardBridge(view);
    auto* channel = new QWebChannel(view);
    channel->registerObject("clipboardBridge", bridge);
    view->page()->setWebChannel(channel);

    QFile webChannelFile(":/qtwebchannel/qwebchannel.js");
    if (webChannelFile.open(QIODevice::ReadOnly)) {
        QWebEngineScript loadWebChannel;
        loadWebChannel.setSourceCode(QString::fromUtf8(webChannelFile.readAll()));
        loadWebChannel.setName("QWebChannel");
        loadWebChannel.setWorldId(QWebEngineScript::MainWorld);
        loadWebChannel.setInjectionPoint(QWebEngineScript::DocumentCreation);
        loadWebChannel.setRunsOnSubFrames(true);
        view->page()->scripts().insert(loadWebChannel);
    }

    QString script = R"(
        (function() {
            function initClipboardBridge() {
                if (typeof QWebChannel === 'undefined') {
                    setTimeout(initClipboardBridge, 50);
                    return;
                }

                new QWebChannel(qt.webChannelTransport, function(channel) {
                    window.clipboardBridge = channel.objects.clipboardBridge;

                    document.addEventListener('copy', function(e) {
                        if (e.clipboardData) {
                            var text = window.getSelection().toString();
                            if (text) {
                                window.clipboardBridge.copyToClipboard(text);
                            }
                        }
                    }, true);

                    if (navigator.clipboard && navigator.clipboard.writeText) {
                        var originalWriteText = navigator.clipboard.writeText.bind(navigator.clipboard);
                        navigator.clipboard.writeText = function(text) {
                            window.clipboardBridge.copyToClipboard(text);
                            return originalWriteText(text).catch(() => {});
                        };
                    }

                    var originalExecCommand = document.execCommand.bind(document);
                    document.execCommand = function(command) {
                        if (command === 'copy') {
                            var text = window.getSelection().toString();
                            if (text) {
                                window.clipboardBridge.copyToClipboard(text);
                            }
                        }
                        return originalExecCommand.apply(document, arguments);
                    };
                });
            }

            initClipboardBridge();
        })();
    )";

    QWebEngineScript webChannelScript;
    webChannelScript.setSourceCode(script);
    webChannelScript.setName("ClipboardBridge");
    webChannelScript.setWorldId(QWebEngineScript::MainWorld);
    webChannelScript.setInjectionPoint(QWebEngineScript::DocumentCreation);
    webChannelScript.setRunsOnSubFrames(true);
    view->page()->scripts().insert(webChannelScript);
}
