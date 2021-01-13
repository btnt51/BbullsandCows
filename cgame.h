#ifndef CGAME_H
#define CGAME_H

#include <QString>
#include <QFile>
#include <random>
#include <ctime>


class CGame
{
public:
    CGame(){isRun = false; isNewGame = false; number.clear(); countTurns= 0;}

    bool getIsRun(){return this->isRun;}
    bool getIsNewGame(){return this->isNewGame;}
    int getCountTurns(){return this->countTurns;}
    void setIsRun(bool rule)    { this->isRun = rule;}
    void setIsNewGame(bool rule){ this->isNewGame = rule;}

    QString turn(QString number);
    QString loadGame();
    QString loadStats();
    void generateNumber();
    void saveGame(QString);
    void saveStats(QString);
    bool isWin(QString num1){return num1 == this->number ? true : false;}



private:
    bool isRun;
    bool isNewGame;
    QString number;
    int countTurns;
};

#endif // CGAME_H
