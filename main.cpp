#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// - R means Reaper's comment
// - Y means Yeager's comment

// In this project for dyanamic arrays we will use vector arrays which
// have automatic memory management making them easier to work with
// instead of new and delete[]

// Spaceship Design
// Bullet design

// Enemy design
// Bullet design

int screen_length = 15;
int screen_width = 30;

void drawGameWindow()
{
    system("CLS");
    for (int i = 0; i < screen_width; i++)
    {
        cout << "*";
    }
    cout << endl;

    for (int i = 0; i < screen_length; i++)
    {
        for (int j = 0; j < screen_width; j++)
        {
            if (j == 0 || j == screen_width - 1)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < screen_width; i++)
    {
        cout << "*";
    }
}

void takeInput();

class Player
{
    int playerHealth = 5;
};

// Work on this class as well - R
class Enemy
{
    int enemyHealth = 1;
};

int main()
{
    // Main game loop
    bool running = true;
    drawGameWindow();
    while (running == true)
    {
        continue;
    }

    return 0;
}