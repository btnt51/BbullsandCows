#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget * widget = new QWidget();
    widget->setLayout(ui->gridLayout);
    ui->textEdit->setReadOnly(true);
    setCentralWidget(widget);
    setWindowTitle("Bulls and cows");
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
    pGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::saveGame()
{
    game.saveGame(ui->textEdit->toPlainText());
}

void MainWindow::loadGame()
{
    QString str = game.loadGame();

    //qDebug() << str;
    //ui->textEdit->clear();
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
