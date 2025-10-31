#include <QWebEnginePage>
#include <QWebEngineNavigationRequest>
#include <QWebEngineNewWindowRequest>
#include <QWebChannel>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QFile>

#include "githubview.h"
#include "constants.h"
#include "settings.h"

GithubView::GithubView(QWidget* parent): QWebEngineView(Constants::webProfile(), parent) {
    connect(page(), &QWebEnginePage::newWindowRequested,this, &GithubView::handleNewWindowRequest);
    connect(page(), &QWebEnginePage::navigationRequested,this, &GithubView::handleNavigationRequest);

    setupClipboardBridge();

    page()->load(Settings::githubUrl());
}

void GithubView::setupClipboardBridge() {
    // Set up QWebChannel to communicate between JavaScript and Qt
    webChannel = new QWebChannel(this);
    webChannel->registerObject("clipboardBridge", &clipboardBridge);
    page()->setWebChannel(webChannel);

    // Load qwebchannel.js first
    QFile webChannelFile(":/qtwebchannel/qwebchannel.js");
    if (webChannelFile.open(QIODevice::ReadOnly)) {
        QString webChannelJs = QString::fromUtf8(webChannelFile.readAll());
        QWebEngineScript loadWebChannel;
        loadWebChannel.setSourceCode(webChannelJs);
        loadWebChannel.setName("QWebChannel");
        loadWebChannel.setWorldId(QWebEngineScript::MainWorld);
        loadWebChannel.setInjectionPoint(QWebEngineScript::DocumentCreation);
        loadWebChannel.setRunsOnSubFrames(true);
        page()->scripts().insert(loadWebChannel);
        webChannelFile.close();
    }

    // Inject JavaScript to intercept clipboard copy events
    QString script = R"(
        (function() {
            function initClipboardBridge() {
                if (typeof QWebChannel === 'undefined') {
                    setTimeout(initClipboardBridge, 50);
                    return;
                }

                new QWebChannel(qt.webChannelTransport, function(channel) {
                    window.clipboardBridge = channel.objects.clipboardBridge;

                    // Intercept clipboard copy operations
                    document.addEventListener('copy', function(e) {
                        if (e.clipboardData) {
                            var text = window.getSelection().toString();
                            if (text) {
                                window.clipboardBridge.copyToClipboard(text);
                            }
                        }
                    }, true);

                    // Intercept navigator.clipboard.writeText (GitHub's primary method)
                    if (navigator.clipboard && navigator.clipboard.writeText) {
                        var originalWriteText = navigator.clipboard.writeText.bind(navigator.clipboard);
                        navigator.clipboard.writeText = function(text) {
                            window.clipboardBridge.copyToClipboard(text);
                            return originalWriteText(text).catch(() => {});
                        };
                    }

                    // Intercept document.execCommand('copy') (GitHub's fallback method)
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
    page()->scripts().insert(webChannelScript);
}

bool GithubView::handleUrlAndEmitSignals(const QUrl& url) {
    if(url.host() == Settings::githubUrl().host())
        return true;

    emit externalNavigationRequested(url);
    return false;
}

void GithubView::handleNavigationRequest(QWebEngineNavigationRequest& request){
    if(!request.isMainFrame()) {
        // github is fetching resources, rich image diffs, the like
        request.accept();
        return;
    }

    if(handleUrlAndEmitSignals(request.url()))
        request.accept();
    else
        request.reject();
}

void GithubView::handleNewWindowRequest(QWebEngineNewWindowRequest& request){
    if(handleUrlAndEmitSignals(request.requestedUrl()))
        request.openIn(page());
}
