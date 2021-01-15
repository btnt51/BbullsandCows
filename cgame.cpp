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

void CGame::generateNumber()
{
    int NUMBER{};
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<int> uid(1111,9999);
    NUMBER = uid(gen);
    number.append(QString::number(NUMBER));
    int t{};
    for(int k = 0; k <= 9;k++)
    {
        for(int j = 0; j < 4;j++)
        {
            if(number[j] == k)
                t++;
            if(t == 2)
                break;
        }
        if(t == 2)
        {
            NUMBER = uid(gen);
            number.append(QString::number(NUMBER));
            k = 0;
        }
    }
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
