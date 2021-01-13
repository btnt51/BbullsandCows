#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget * widget = new QWidget();
    widget->setLayout(ui->gridLayout);
    setCentralWidget(widget);
    setWindowTitle("Bulls and cows");
    ui->plainTextEdit->setPlainText("If u want to start a new game use shortcut CTRL+N or trigger in menu "
                                    "\"GAME\"\\\"new game\" \n"
                                    "If u want to load your previous game trigger in "
                                    "menu \"GAME\"\\\"load previous game\"");
    ui->pushButton->setVisible(false);
    ui->lineEdit->setVisible(false);
    connect(ui->actionSave_game, SIGNAL(triggered()), this, SLOT(saveGame()));
    connect(ui->actionLoad_previous_game, SIGNAL(triggered()), this, SLOT(loadGame()));
    connect(ui->actionNew_Game,SIGNAL(triggered()), this, SLOT(newGame()));
    game.setIsNewGame(false);
    game.setIsRun(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::saveGame()
{

}

void MainWindow::loadGame()
{

}


void MainWindow::on_pushButton_clicked()
{
    if(game.getIsNewGame())
    {
        if(game.getIsRun())
        {
            if(ui->lineEdit->text().length() < 4 || ui->lineEdit->text().length() > 4)
                return;

            if(game.isWin(ui->lineEdit->text()))
            {
                ui->plainTextEdit->appendPlainText(ui->lineEdit->text()+" Is right number. You win!");
                game.setIsRun(false);

                ui->plainTextEdit->appendPlainText("If u want to start a new game use shortcut CTRL+N or trigger in menu "
                                                "\"GAME\"\\\"new game\" \n"
                                                "If u want to load your previous game trigger in "
                                                "menu \"GAME\"\\\"load previous game\"");
                ui->pushButton->setVisible(false);
                ui->lineEdit->setVisible(false);
            }
            else
            {
                ui->plainTextEdit->appendPlainText(ui->lineEdit->text()+ " -"+game.turn(ui->lineEdit->text()));
                ui->lineEdit->clear();
            }
        }
    }
}

void MainWindow::newGame()
{
    game.setIsNewGame(true);
    game.setIsRun(true);
    game.generateNumber();
    ui->plainTextEdit->clear();
    ui->pushButton->setVisible(true);
    ui->lineEdit->setVisible(true);
}
