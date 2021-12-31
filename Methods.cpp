#include"Header.h"
#include <iostream>
#include <Windows.h>
#include <time.h>

void snake::move(Direction DIR)
{
    for (int i = X.size() - 1; i > 0; i--)
    {
        X[i] = X[i - 1];
        Y[i] = Y[i - 1];
    }
    switch (DIR)
    {
        case LEFT:
        {
            X[0] -= 1;
            break;
        }
        case RIGHT:
        {
            X[0] += 1;
            break;
        }
        case UP:
        {
            Y[0] -= 1;
            break;
        }
        case DOWN:
        {
            Y[0] += 1;
            break;
        }
    }
}

void apple::set(snake &Snake)
{
    bool again = true;
    while (again)
    {
        again = false;
        X = rand() % 20;
        Y = rand() % 20;
        for (int i = 0; i < Snake.X.size(); i++)
        {
            if (X == Snake.X[i] && Y == Snake.Y[i])
                again = true;
        }
    }
}

bool snake::check()
{
    if (X[0] < 0 || X[0] > 19 || Y[0] < 0 || Y[0] > 19) return true;
    for (int i = 1; i < X.size(); i++)
    {
        if (X[i] == X[0] && Y[i] == Y[0]) return true;
    }
    return false;
}