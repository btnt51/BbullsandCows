#ifndef CGAME_H
#define CGAME_H

#include <QObject>
#include <QString>
#include <QFile>
#include <random>
#include <ctime>
#include <QDebug>


class CGame : public QObject
{
    Q_OBJECT
public:
    CGame()
    {
        isRun = false;
        isNewGame = false;
        number.clear();
        countTurns= 0;
        minCountTurns = 0;
        totalGames = 0;
    }
    virtual ~CGame(){};

    bool getIsRun()             {return this->isRun;}
    bool getIsNewGame()         {return this->isNewGame;}
    int getCountTurns()         {return this->countTurns;}
    int getMinTurns()           {return this->minCountTurns;}
    int getTotalGames()         {return this->totalGames;}
    void setIsRun(bool rule)    {this->isRun = rule;}
    void setIsNewGame(bool rule){this->isNewGame = rule; totalGames++; emit valueChanged();}

    QString turn(QString number);
    QString loadGame();
    QString loadStats();
    void generateNumber();
    void saveGame(QString);
    void saveStats();
    void checkstas(){if(minCountTurns > countTurns) minCountTurns=countTurns; emit valueChanged();}
    bool isWin(QString num1)    {return num1 == this->number;}

public slots:
    void startingGame();
    void pauseGame();

signals:
    void valueChanged();


private:
    bool isRun;
    bool isNewGame;
    QString number;
    int countTurns;
    int minCountTurns;
    int totalGames;
};

#endif // CGAME_H
