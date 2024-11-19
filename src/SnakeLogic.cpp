#include "SnakeLogic.h"

SnakePart::SnakePart()
    : SnakePart(0,0)
{
}

SnakePart::SnakePart(int gx, int gy)
    : gx(gx), gy(gy)
{
}

SnakeLogic::SnakeLogic()
{
    snake[0] = SnakePart(1,0);
    snake[1] = SnakePart(0,0);
}

void SnakeLogic::move(Direction d)
{
    // shift snake back
    for (int i = 0; i < size; i++)
    {
        snake[size - i - 1] = snake[size - i];
    }

    // Update position of head
    if (d == Direction::Up)
    {
        snake[0].gy--;
    }
    else if (d == Direction::Down)
    {
        snake[0].gy++;
    }
    else if (d == Direction::Left)
    {
        snake[0].gx--;
    }
    else if (d == Direction::Right)
    {
        snake[0].gx++;
    }
}

const SnakePart * SnakeLogic::getSnake()
{
    return snake;
}

const int SnakeLogic::getSize()
{
    return size;
}