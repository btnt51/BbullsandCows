#include "howtoplay.h"
#include "ui_howtoplay.h"

howToPlay::howToPlay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::howToPlay)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    ui->textEdit->setText("Kon4a mangysta");
}

howToPlay::~howToPlay()
{
    delete ui;
}

void howToPlay::setDarkTheme()
{
    ui->textEdit->setStyleSheet("background-color:rgb(85, 87, 83); color:white");
    this->setStyleSheet("background-color:rgb(46, 52, 54)");
}

void howToPlay::setLightTheme()
{
    ui->textEdit->setStyleSheet("");
    this->setStyleSheet("");
}
