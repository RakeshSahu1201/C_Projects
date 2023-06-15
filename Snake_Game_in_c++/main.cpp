#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Game.h"

using namespace std;


//void snakeUp(int,int);
//void snakeDown(int,int);
//void snakeLeft(int,int);
//void snakeRight(int,int);
//void startGame();

int main()
{
    Game obj;
    obj.frontView();
    obj.border();
    obj.snakeFood();
    obj.startGame();

    return 0;
}



