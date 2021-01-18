#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cgame.h>
#include "howtoplay.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void saveGame();
    void loadGame();
    void on_pushButton_clicked();
    void newGame(bool t = true);
    void pGame();
    void setStats(bool t = true);
    void setDarkTheme();
    void setLightTheme();
    void openHelp();


private:
    Ui::MainWindow *ui;
    CGame game;
    QWidget * widget;
    howToPlay * hwt;
};
#endif // MAINWINDOW_H
