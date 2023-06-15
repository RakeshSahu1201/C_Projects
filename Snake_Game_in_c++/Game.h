#ifndef GAME_H
#define GAME_H
#endif // GAME_H
using namespace std;


class Game
{
    private:
        int i;
        int j;
        int Food_XCord;
        int Food_YCord;
        string snake;
        string snakeRemove;
        int count;
    public:
        Game();
        virtual ~Game();
        char snakeUp();
        char snakeDown();
        char snakeLeft();
        char snakeRight();
        void startGame();
        void border();
        void frontView();
        void snakeFood();
        int snakeShouldGrow();
        void snakeGrow();
        void snakeGrowRemove();

};

void Consolepoint(int,int);

