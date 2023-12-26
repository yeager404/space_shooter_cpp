#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <chrono>

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

long long getTime();

class Player
{
private:
    int playerHealth = 5;
    vector<char> bullet{'B'};

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

    PlayerPart *playerParts[4]{&playerHead, &playerCenter, &playerRight, &playerLeft};

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
private:
    char enemyCharacter = 'Y';
    int enemyHealth = 1;
    int enemy_spawn_speed = 5000;
    int enemy_movement_speed = 2000;
    long long enemy_move_time = getTime();
    long long enemy_spawn_time = getTime();

public:
    vector<int> enemy_pos_x;
    vector<int> enemy_pos_y;

    void Logic(int width)
    {
        if (getTime() - enemy_move_time >= enemy_movement_speed)
        {
            for (size_t i{0}; i < enemy_pos_y.size(); i++)
                enemy_pos_y[i] += 1;
            enemy_move_time = getTime();
        }

        if (getTime() - enemy_spawn_time >= enemy_spawn_speed)
        {
            int new_enemy_x_pos = rand() % (width - 1) + 1;
            int new_enemy_y_pos = 0;
            enemy_pos_x.push_back(new_enemy_x_pos);
            enemy_pos_y.push_back(new_enemy_y_pos);
            enemy_spawn_time = getTime();
        }
    }

    Enemy(int width)
    {
        int first_enemy_x_pos = rand() % width;
        int first_enemy_y_pos = 0;
        enemy_pos_x.push_back(first_enemy_x_pos);
        enemy_pos_y.push_back(first_enemy_y_pos);
    }
};

void drawGameWindow(int screen_width, int screen_length, char borderCharacter, Player player, Enemy enemy)
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
            for (size_t k{0}; k < 4; k++)
            {
                if (player.playerParts[k]->xPos == j && player.playerParts[k]->yPos == i)
                {
                    cout << player.playerParts[k]->character;
                    matched = true;
                }
            }

            for (size_t enemy_spawner{0}; enemy_spawner < enemy.enemy_pos_x.size(); enemy_spawner++)
            {
                if (enemy.enemy_pos_x[enemy_spawner] != -1)
                {
                    if (i == enemy.enemy_pos_y[enemy_spawner] && j == enemy.enemy_pos_x[enemy_spawner])
                    {
                        cout << "Y";
                        // new_enemy.Logic();
                        matched = true;
                    }
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

long long getTime()
{
    // Get the current time point
    auto currentTime = std::chrono::system_clock::now();

    // Convert the time point to milliseconds
    auto duration = currentTime.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    return milliseconds;
}

int main()
{
    int width = 30;
    int height = 15;
    int framerate = 1;
    char borderCharacter = '*';
    Player player(25, 14);
    Enemy enemy(width);
    char input;

    // Main game loop
    bool running = true;
    while (running == true)
    {
        input = takeInput();
        if (input == 'Q')
            running = false;
        drawGameWindow(width, height, borderCharacter, player, enemy);
        player.movePlayer(input);
        enemy.Logic(width);

        Sleep(1000 / framerate);
    }

    return 0;
}