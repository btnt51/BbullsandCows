#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget = new QWidget();
    widget->setLayout(ui->gridLayout);
    ui->textEdit->setReadOnly(true);
    setCentralWidget(widget);
    setWindowTitle("Bulls and cows");
    hwt = new howToPlay();
    ui->textEdit->setPlaceholderText("If u want to start a new game use shortcut CTRL+N or trigger in menu "
                                    "\"GAME\"\\\"new game\" \n"
                                    "If u want to load your previous game trigger in "
                                    "menu \"GAME\"\\\"load previous game\""
                                    "\n If you want to pause use shortcut CTRL+P or trigger in menu"
                                    "\"GAME\"\\\"Pause game\""
                                    "To unpuase game use the same shortcut or trigger in menu");
    connect(ui->actionSave_game, SIGNAL(triggered()), this, SLOT(saveGame()));
    connect(ui->actionLoad_previous_game, SIGNAL(triggered()), this, SLOT(loadGame()));
    connect(ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(ui->actionNew_Game, SIGNAL(triggered()), &game, SLOT(startingGame()));
    connect(ui->actionPause_game, SIGNAL(triggered()), &game, SLOT(pauseGame()));
    connect(ui->actionPause_game, SIGNAL(triggered()), this, SLOT(pGame()));
    connect(ui->actionPause_game, SIGNAL(triggered()), this, SLOT(saveGame()));
    connect(ui->actionDark_theme, SIGNAL(triggered()), this, SLOT(setDarkTheme()));
    connect(ui->actionLight_theme, SIGNAL(triggered()), this, SLOT(setLightTheme()));
    connect(ui->actionHow_to_play, SIGNAL(triggered()), this, SLOT(openHelp()));
    connect(&game, SIGNAL(valueChanged()), this, SLOT(setStats()));
    setStats(false);
    pGame();
}

MainWindow::~MainWindow()
{
    game.saveStats();
    delete ui;
    delete widget;
    delete hwt;
}


void MainWindow::saveGame()
{
    game.saveGame(ui->textEdit->toPlainText());
}

void MainWindow::loadGame()
{
    QString str = game.loadGame();
    ui->textEdit->append(str);
    game.setIsRun(true);
    newGame(false);
}


void MainWindow::on_pushButton_clicked()
{
    if(game.getIsRun())
    {
        if(ui->lineEdit->text().length() < 4 || ui->lineEdit->text().length() > 4)
            return;

        if(game.isWin(ui->lineEdit->text()))
        {
            game.checkstas();
            ui->textEdit->append(ui->lineEdit->text()+" Is right number. You win!");
            game.setIsRun(false);

            ui->textEdit->append("If u want to start a new game use shortcut CTRL+N or trigger in menu "
                                            "\"GAME\"\\\"new game\" \n"
                                            "If u want to load your previous game trigger in "
                                            "menu \"GAME\"\\\"load previous game\"");
            pGame();
        }
        else
        {
            ui->textEdit->append(ui->lineEdit->text()+ " -"+game.turn(ui->lineEdit->text()));
            ui->lineEdit->clear();
        }
    }
}

void MainWindow::newGame(bool t)
{  
    if(t)
        ui->textEdit->clear();
    ui->pushButton->setVisible(true);
    ui->lineEdit->setVisible(true);
}

void MainWindow::pGame()
{
    if(!game.getIsRun())
    {
        ui->pushButton->setVisible(false);
        ui->lineEdit->setVisible(false);
    }
    else
        newGame(false);

}

void MainWindow::setStats(bool t)
{
    if(t)
    {
        ui->minimalTurns->setText("Minimal turns "+ QString::number(game.getMinTurns()));
        ui->countsOfGames->setText("Total games played " + QString::number(game.getTotalGames()));
    }
    else
    {
        QString str = game.loadStats();
        int index = str.indexOf("_");
        QString  totalGames;
        for(int i = 0; i < index;i++)
            totalGames += str[i];
        QString minTurns;
        index++;
        for(int i = index; i < str.length();i++)
            minTurns += str[i];
        ui->minimalTurns->setText("Minimal turns "+minTurns);
        ui->countsOfGames->setText("Total games played " + totalGames);
    }
}

void MainWindow::setDarkTheme()
{
    hwt->setDarkTheme();
    ui->statusbar->setStyleSheet("background-color:rgb(46, 52, 54)");                   //цветовая тема для отображаемых окон
    widget->setStyleSheet("background-color:rgb(46, 52, 54)");
    this->setStyleSheet("background-color:rgb(46, 52, 54)");
    ui->textEdit->setStyleSheet("background-color:rgb(85, 87, 83); color:white");
    ui->lineEdit->setStyleSheet("background-color:rgb(85, 87, 83); color:white");
    ui->pushButton->setStyleSheet("background-color:rgb(85, 87, 83); color:white");
    ui->menubar->setStyleSheet("background-color:rgb(85, 87, 83); color:white");
    ui->menuMenu->setStyleSheet("background-color:rgb(85, 87, 83); color:white");
    ui->menuGame->setStyleSheet("background-color:rgb(85, 87, 83); color:white");
    ui->menuHelp->setStyleSheet("background-color:rgb(85, 87, 83); color:white");
    ui->minimalTurns->setStyleSheet("color:white");
    ui->countsOfGames->setStyleSheet("color:white");
}

void MainWindow::setLightTheme()
{
    hwt->setLightTheme();
    ui->statusbar->setStyleSheet("");
    widget->setStyleSheet("");
    this->setStyleSheet("");
    ui->lineEdit->setStyleSheet("");
    ui->textEdit->setStyleSheet("");
    ui->pushButton->setStyleSheet("");
    ui->menubar->setStyleSheet("");
    ui->menuMenu->setStyleSheet("");
    ui->menuGame->setStyleSheet("");
    ui->menuHelp->setStyleSheet("");
    ui->minimalTurns->setStyleSheet("");
    ui->countsOfGames->setStyleSheet("");
}

void MainWindow::openHelp()
{
    hwt->show();
}
