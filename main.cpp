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
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <windows.h>

#include <chrono>

#include <random>
#include <chrono>
#include <time.h>

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

class Player
{
private:
    int playerHealth = 5;
    char bulletCharacter = '|';
    float bulletFrequencyPerSecond = 1;
    float bulletSpeedPerSecond = 15;
    long long bulletShootClock = getTime();
    long long bulletMoveClock = getTime();

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

    struct Bullet
    {
        char character;
        int xPos = 0;
        int yPos = 0;

        Bullet(char character, int xPos, int yPos)
        {
            this->character = character;
            this->xPos = xPos;
            this->yPos = yPos;
        }
    };

public:
    vector<Bullet> bullet_array;

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

    void shootBullet()
    {
        if ((getTime() - bulletShootClock) > (1000 / bulletFrequencyPerSecond))
        {
            Bullet bullet(bulletCharacter, playerHead.xPos, playerHead.yPos - 1);
            bullet_array.push_back(bullet);
            bulletShootClock = getTime();
        }

        if ((getTime() - bulletMoveClock) > (1000 / bulletSpeedPerSecond))
        {
            for (size_t i{0}; i < bullet_array.size(); i++)
            {
                bullet_array[i].yPos--;
                if (bullet_array[i].yPos < -1)
                {
                    bullet_array.erase(bullet_array.begin() + i);
                }
            }
            bulletMoveClock = getTime();
        }
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

            for (size_t k{0}; k < 4; k++)
            {
                if (player.playerParts[k]->xPos == j && player.playerParts[k]->yPos == i)
                {
                    cout << player.playerParts[k]->character;
                    matched = true;
                }
            }

            for (size_t bullet_counter{0}; bullet_counter < player.bullet_array.size(); bullet_counter++)
            {
                if (player.bullet_array[bullet_counter].xPos == j && player.bullet_array[bullet_counter].yPos == i)
                {
                    cout << player.bullet_array[bullet_counter].character;
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
    srand(time(0));
    int width = 30;
    int height = 15;
    int framerate = 60;
    char borderCharacter = '*';
    Player player(25, height - 1);
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

        if (input == 'Q')
            running = false;

        drawGameWindow(width, height, borderCharacter, player, enemy);

        player.movePlayer(input);
        player.shootBullet();

        Sleep(1000 / framerate);
    }

    return 0;
}
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