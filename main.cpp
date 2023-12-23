#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <windows.h>

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


void drawGameWindow(int screen_width, int screen_length, char borderCharacter)
{
    system("CLS");
    for (int i = 0; i < screen_width; i++)
    {
        cout << borderCharacter;
    }
    cout << endl;

    for (int i = 0; i < screen_length; i++)
    {
        for (int j = 0; j < screen_width; j++)
        {
            if (j == 0 || j == screen_width - 1)
                cout << borderCharacter;
            else
                cout << " ";
        }
        cout << endl;
    }


    for (int i = 0; i < screen_width; i++)
    {
        cout << borderCharacter;
    }
}


char takeInput() 
{
    char key;
    if (!_kbhit())
    {
        return 'N';
    }

    key = getch();
        switch (key)
        {
            case 'w': // Up arrow
                return 'W';
                break;
            case 's': // Down arrow
                return 'S';
                break;
            case 'a': // Left arrow
                return 'A';
                break;
            case 'd': // Right arrow
                return 'D';
                break;
            default:
                return toupper(key);
                break;
        }
}


class Player
{
private:
    int playerHealth = 5;
    char spaceshipChar = 'S';
    int playerPosX = 5;
    int playerPosY = 5;
    vector<char> bullet ['B'];

public:
    void movePlayer(char input) 
    {
        if (input == 'A') 
        {
            playerPosX --;
        }
        else if (input == 'D')
        {
            playerPosX ++;
        }
    }
};


// Work on this class as well - R
class Enemy
{
    int enemyHealth = 1;
};


int main()
{
    int width = 30;
    int height = 15;
    int framerate = 24;
    char borderCharacter = '*';
    Player player;
    char input;

    // Main game loop
    bool running = true;
    while (running == true)
    {
        input = takeInput();
        if (input == 'Q') running = false;
        drawGameWindow(width, height, borderCharacter);
        player.movePlayer(input);
        Sleep(1000/framerate);
    }

    return 0;
}