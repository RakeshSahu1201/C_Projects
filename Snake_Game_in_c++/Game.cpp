#include <iostream>
#include "conio.h"
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Game.h"

using namespace std;

Game::Game()//ctor
{
    count = 1;
    snake.insert(0,"+");
    snakeRemove.insert(0,"\b ");
}

char Game::snakeUp()
{
    char ch = '\0';
    for(;;j--)
    {
        if(kbhit())
        {
            ch = getch();
            return ch;
        }
        if(snakeShouldGrow())
            exit(0);
        if(j>=0)
        {
            Consolepoint(i,j);
            cout<<snake;
            Sleep(100);
            cout<<snakeRemove;
        }
        else
        {
            j=29;
        }
        if(kbhit())
        {
            ch = getch();
            return ch;
        }
    }
}
char Game::snakeDown()
{
    char ch = '\0';
    for(;;j++)
    {
        if(kbhit())
        {
            ch = getch();
            return ch;
        }
        if(snakeShouldGrow())
            exit(0);
        if(j<29)
        {
            Consolepoint(i,j);
            cout<<snake;
            Sleep(100);
            cout<<snakeRemove;
        }
        else
        {
            j=0;
        }
        if(kbhit())
        {
            ch = getch();
            return ch;
        }
    }
}
char Game::snakeLeft()
{
    char ch = '\0';
    for(;;i--)
    {
        if(kbhit())
        {
            ch = getch();
            return ch;
        }
        if(snakeShouldGrow())
            exit(0);
        if(i>=0)
        {
            Consolepoint(i,j);
            cout<<snake;
            Sleep(100);
            cout<<snakeRemove;
        }
        else
        {
            i=80;
        }
        if(kbhit())
        {
            ch = getch();
            return ch;
        }
    }
}
char Game::snakeRight()
{
    char ch = '\0';
    for(;;i++)
    {
        if(kbhit())
        {
            ch = getch();
            return ch;
        }
        if(snakeShouldGrow())
        {
            snakeGrow();
        }
        if(j<=80)
        {
            Consolepoint(i,j);
            cout<<snake;
            Sleep(100);
            cout<<snakeRemove;
        }
        else
        {
            i=0;
        }
        if(kbhit())
        {
            ch = getch();
            return ch;
        }
    }
}


void Game::startGame()
{
    char ch;
    srand(time(NULL));
//    i = ((rand() %(20 - 10 + 1)) + 10);
//    srand(time(NULL));
//    j = ((rand() %(20 - 10 + 1)) + 10);
    i = (rand() % 23) + 1;
    j = (rand() % 27) + 1;
    getch();
    while(1)
    {
        if(kbhit())
            ch = getch();
        switch(ch)
        {
            case 72:
                ch = snakeUp();
                break;
            case 80:
                ch = snakeDown();
                break;
            case 75:
                snakeLeft();
                break;
            case 77:
                snakeRight();
                break;
            case '0':
                break;
        }
        if(ch=='0')
            break;
    }
}

void Game::border()
{
    int a,b;
    a = b = 0;
    //UP SIDE BORDER
    Consolepoint(a,b);
    for(int k = 1;k<=30;k++)
        cout<<"* ";

    //LEFT SIDE BORDER
    Consolepoint(a,b);
    for(int k = 1;k<29;k++)
    {
        cout<<"*";
        if(k<=27)
            cout<<endl;
    }

    //DOWN SIDE BORDER
    a = 0;
    b = 28;
    Consolepoint(a,b);
    for(int k = 1;k<=29;k++)
        cout<<"* ";

    //RIGHT SIDE BORDER
    a = 58;
    b = 28;
    for(int k = 1;k<29;k++,b--)
    {
        Consolepoint(a,b);
        cout<<"*";
    }
}

void Game::frontView()
{
    Consolepoint(14,6);
    cout<<".....Welcome to the Snake Game.....";
    Consolepoint(20,9);
    cout<<"1.START_GAME";
    Consolepoint(20,10);
    cout<<"2.HIGH_SCORE";
    Consolepoint(20,11);
    cout<<"3.QUIT";
    _getch();
}

void Game::snakeFood()
{
    srand(time(NULL));
//    Food_XCord = ((rand() %(20 - 10 + 1)) + 10);
//    srand(time(NULL));
//    Food_YCord = ((rand() %(20 - 10 + 1)) + 10);
    Food_XCord = (rand() % 70) + 1;
    Food_YCord = (rand() % 20) + 1;
//    cout<<Food_XCord<<"   "<<Food_YCord<<endl;
    Consolepoint(Food_XCord,Food_YCord);

    cout<<"Food";
}

int Game::snakeShouldGrow()
{
    if(i == Food_XCord && j== Food_YCord)
    {
        count++;
        return 1;
    }
    else
        return 0;
}

void Game::snakeGrow()
{
    for(int i= 1;i<=count;i++)
    {
        snake.insert(snake.length(),"+");
        snakeRemove.insert(0,"\b");
    }
    for(int i= 1;i<=count;i++)
    {
        snakeRemove.insert(snakeRemove.length()," ");
    }

}

void Game::snakeGrowRemove()
{


}
void Consolepoint(int x,int y)
{

    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}


Game::~Game()
{
    //dtor
}
