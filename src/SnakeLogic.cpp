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

    d = Direction::Right;
}

/**
 * Moves the snake.
 * 
 * Note: snake can't move backwards. If user tries to move backwards 
 * the given direction will be ignored, and snake will move forward.
 */
void SnakeLogic::move(Direction d)
{
    // Ignore direction that moves snake backwards
    if 
    (   
        (this->d == Direction::Right && d == Direction::Left) ||
        (this->d == Direction::Left && d == Direction::Right) ||
        (this->d == Direction::Up && d == Direction::Down)    ||
        (this->d == Direction::Down && d == Direction::Up)
    )
    {
        d = this->d;
    }

    // shift snake back
    for (int i = size - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
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

    this->d = d;
}

const SnakePart * SnakeLogic::getSnake()
{
    return snake;
}

const int SnakeLogic::getSize()
{
    return size;
}