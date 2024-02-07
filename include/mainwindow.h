#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QWebEngineView>
#include <QWebEngineProfile>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QSplitter splitter;
    QWebEngineProfile profile;
    QWebEngineView leftView;
    QWebEngineView rightView;
};
#endif // MAINWINDOW_H
