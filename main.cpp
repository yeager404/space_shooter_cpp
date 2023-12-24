#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <time.h>
#include <random>

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
//  ^
// ^o^

// Enemy design
// Y


class Player
{
private:
    int playerHealth = 5;
    vector<char> bullet {'B'};
    

    struct PlayerPart 
    {
        char character = ' ';
        int xPos = 0;
        int yPos = 0;
        
        PlayerPart(char character, int xPos, int yPos)
        {
            this->character = character;
            this->xPos = xPos;
            this->yPos = yPos;
        }
    }; 

    
public:
    PlayerPart playerHead{'^', 0, 0};
    PlayerPart playerCenter{'o', 0, 0};
    PlayerPart playerRight{'^', 0, 0};
    PlayerPart playerLeft{'^', 0, 0};

    PlayerPart* playerParts[4] {&playerHead, &playerCenter, &playerRight, &playerLeft};

    Player(int xPos, int yPos)
    {
        playerCenter.xPos = xPos;
        playerCenter.yPos = yPos;

        playerHead.xPos = xPos;
        playerHead.yPos = yPos - 1;

        playerRight.xPos = xPos + 1;
        playerRight.yPos = yPos;

        playerLeft.xPos = xPos - 1;
        playerLeft.yPos = yPos;
    }


    void movePlayer(char input) 
    {
        if (input == 'A') 
        {
            playerCenter.xPos--;
            playerHead.xPos--;
            playerRight.xPos--;
            playerLeft.xPos--;
        }
        else if (input == 'D')
        {
            playerCenter.xPos++;
            playerHead.xPos++;
            playerRight.xPos++;
            playerLeft.xPos++;
        }
    }
};


// Work on this class as well - R
class Enemy
{
    int enemyHealth = 1;
};


void drawGameWindow(int screen_width, int screen_length, char borderCharacter, Player player)
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

            bool matched = false;
            for (size_t k {0}; k < 4; k++)
            {
                if (player.playerParts[k]->xPos == j && player.playerParts[k]->yPos == i) 
                {
                    cout << player.playerParts[k]->character;     
                    matched = true;
                }
            } 
            if (!matched)
            {
                cout << " ";
            }
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


int main()
{
    srand(time(0));
    int width = 30;
    int height = 15;
    int framerate = 60;
    char borderCharacter = '*';
    Player player(25, 14);
    char input;
    int clock = time(0);

    // Main game loop
    bool running = true;
    while (running == true)
    {
        input = takeInput();
        if (input == 'Q') running = false;
        drawGameWindow(width, height, borderCharacter, player);
        player.movePlayer(input);
        Sleep(1000/framerate);
    }

    return 0;
}