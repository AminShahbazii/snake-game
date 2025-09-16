#include <iostream>
#include <coniopp.h>
#include <unistd.h>
using namespace std;
#define clear() cout << "\033[H\033[J" << endl;
char kyebord;
int snakesize = 1;

void hit(char map[][30], int snake[][2])
{
    if (snake[0][0] > 30 || snake[0][0] <= 0)
    {
        cout << "You lose." << endl;
        exit(1);
    }
    if (snake[0][1] >= 30 || snake[0][1] <= 0)
    {
        cout << "You lose." << endl;
        exit(1);
    }

    for (int i = 1; i < snakesize; i++)
    {
        if (snake[i][0] == snake[0][0] && snake[i][1] == snake[0][1])
        {
            cout << "You lose." << endl;
            exit(1);
        }
    }
}

void apple(char map[][30], int snake[][2], int *index, int *indey)
{
    map[*index][*indey] = '0';
    if (*index == snake[0][0] && *indey == snake[0][1])
    {
        *index = (rand() % 27) + 1;
        *indey = (rand() % 27) + 1;
        snakesize += 1;
    }
}

void output(char map[][30])
{
    for (int i = 0; i < 30; i++)
    {

        for (int j = 0; j < 30; j++)
        {
            if (i == 0 || i == 29)
                cout << "-";
            else if (j == 0 || j == 29)
                cout << "|";
            else
                cout << map[i][j];
        }
        cout << endl;
    }
}

void commit(char map[][30], int snake[][2])
{

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            bool cleaner = false;
            for (int l = 1; l <= snakesize; l++)
            {

                if (snake[l][0] == i && snake[l][1] == j)
                {
                    map[i][j] = '*';
                    cleaner = true;
                }
            }
            if (!cleaner)
            {
                map[i][j] = ' ';
            }
        }
    }
}

void changing(int snake[][2])
{
    int n, m, a, b;
    n = snake[0][0];
    m = snake[0][1];
    for (int i = 1; i <= snakesize; i++)
    {
        a = snake[i][0];
        b = snake[i][1];
        snake[i][0] = n;
        snake[i][1] = m;
        n = a;
        m = b;
    }
}

void move(int snake[][2])
{
    clear();
    switch (kyebord)
    {
    case 'w':
        snake[0][0] -= 1;
        break;
    case 's':
        snake[0][0] += 1;
        break;
    case 'd':
        snake[0][1] += 1;
        break;
    case 'a':
        snake[0][1] -= 1;
        break;
    }
}

int main()
{

    char map[30][30];
    int snake[784][2];
    snake[0][0] = 5;
    snake[0][1] = 5;
    int index, indey;
    index = (rand() % 27) + 1;
    indey = (rand() % 27) + 1;
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            map[i][j] = ' ';
        }
    }
    while (true)
    {
        if (kbhit())
        {
            kyebord = getch();
        }
        changing(snake);
        commit(map, snake);
        move(snake);
        apple(map, snake, &index, &indey);
        hit(map, snake);
        output(map);
        usleep(100000);
    }
}