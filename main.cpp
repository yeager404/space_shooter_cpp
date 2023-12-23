#include <iostream>
#include <stdio.h>
#include <vector>
#include <conio.h>

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



void drawGameWindow();
// Give this a try - R


char takeInput() 
{
    char key;
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
            // case 72: // Up arrow
            //     return 'W';
            //     break;
            // case 80: // Down arrow
            //     return 'S';
            //     break;
            // case 75: // Left arrow
            //     return 'A';
            //     break;
            // case 77: // Right arrow
            //     return 'D';
            //     break;
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

    Player player;
    char input;
    // Main game loop
    bool running = true;
    while (running == true) 
    {
        input = takeInput();
        if (input == 'Q') running = false;
        drawGameWindow();
        player.movePlayer(input);
    }

    return 0;
}