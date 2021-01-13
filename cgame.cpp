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
