#include "cgame.h"

QString CGame::turn(QString Number)
{
    countTurns++;
    int cows={};
    int bulls={};
    for(int i =0; i < 4;i++)
    {
        for(int j = 0; j < 4;j++)
        {
            if(Number[j] == number[i] && j == i)
                bulls++;
            else if(Number[j] == number[i])
                cows++;
        }
    }
    if(bulls == 1 && cows == 1)
        return "There is " + QString::number(bulls) +" bull and " + QString::number(cows) + " cow";
    else if((bulls > 1 ||  bulls == 0) && cows == 1)
        return "There is " + QString::number(bulls) +" bulls and " + QString::number(cows) + " cow";
    else if((bulls > 1 ||  bulls == 0) && (cows > 1 || cows == 0))
        return "There is " + QString::number(bulls) +" bulls and " + QString::number(cows) + " cows";
    else if(bulls == 1  && (cows > 1 || cows == 0))
        return "There is " + QString::number(bulls) +" bull and " + QString::number(cows) + " cows";
    else return "zalupa";

}

QString CGame::loadGame()
{
    QFile file("D:\\lastGame.txt");
    QString result;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        int c = 0;
        //in.setCodec("UTF-8");
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if(c == 0)
                this->number = line;
            else if(c == 1)
                this->countTurns = line.toInt();
            else
                result.append(line+"\n");
            c++;
        }
//        qDebug() << result;
    }
    file.close();
    return result;
}

QString CGame::loadStats()
{
    QFile file("D:\\statsBullsAndCows.txt");
    QString result;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        result = file.readLine();
        qDebug() << result;
    }
    file.close();
    int index = result.indexOf("_");
    QString  totalGames;
    for(int i = 0; i < index;i++)
        totalGames += result[i];
    QString minTurns;
    index++;
    for(int i = index; i < result.length();i++)
        minTurns += result[i];
    this->minCountTurns = minTurns.toInt();
    this->totalGames = totalGames.toInt();
    return result;
}

void CGame::generateNumber()
{

    std::mt19937 gen(time(nullptr)*this->totalGames);
    std::uniform_int_distribution<int> uid(1000,9999);
    while(true)
    {
        number.clear();
        int Number = uid(gen);
        number.append(QString::number(Number));
        bool isNumberCondition =(number[0] == number[1]
                || number[0] == number[2] || number[0] == number[3]
                || number[1] == number[2] || number[1] == number[3]
                || number[2] == number[3]);
        if(isNumberCondition)
            number.clear();
        else break;
    }
    qDebug() << number;
}

void CGame::saveGame(QString str)
{
    QFile file("D:\\lastGame.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(number.toUtf8());
        qDebug() << number;
        file.write("\n"+QString::number(countTurns).toUtf8());
        file.write("\n");
        qDebug() << "O4ko mangysta! Tbi popal";
        file.write(str.toUtf8());
        qDebug() << str;
    }
    file.close();
}

void CGame::saveStats()
{
    QFile file("D:\\statsBullsAndCows.txt");
    QString result = QString::number(this->totalGames)+"_"+QString::number(this->minCountTurns);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        file.write(result.toUtf8());
    file.close();
}

void CGame::startingGame()
{
    this->setIsNewGame(true);
    this->setIsRun(true);
    this->generateNumber();
}

void CGame::pauseGame()
{
    if(this->getIsRun()==true)
        this->setIsRun(false);
    else
        this->setIsRun(true);
}
