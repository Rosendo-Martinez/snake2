#include "SnakeLogic.h"
#include <cstdlib>
#include <ctime>

SnakePart::SnakePart()
    : SnakePart(0,0)
{
}

SnakePart::SnakePart(int gx, int gy)
    : gx(gx), gy(gy)
{
}

Apple::Apple()
    : Apple(0,0)
{
}

Apple::Apple(int gx, int gy)
    : gx(gx), gy(gy)
{
}

SnakeLogic::SnakeLogic()
{
    snake[0] = SnakePart(1,0);
    snake[1] = SnakePart(0,0);

    d = Direction::Right;

    std::srand(std::time(nullptr)); // use current time as seed for random generator
}

/**
 * Moves the snake.
 * 
 * Note: snake can't move backwards. If user tries to move backwards 
 * the given direction will be ignored, and snake will move forward.
 */
void SnakeLogic::move(Direction d)
{
    if (ateAppleLastMove)
    {
        // Snake ate apple last move, so it grows this move.
        size++;
        ateAppleLastMove = false;
    }

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
    movesCount++;
    eatApple();
    generateApple();
}

const SnakePart * SnakeLogic::getSnake()
{
    return snake;
}

const int SnakeLogic::getSize()
{
    return size;
}

const Apple * SnakeLogic::getApples()
{
    return apples;
}

const int SnakeLogic::getSizeApples()
{
    return appleSize;
}

/**
 * Checks if apple can be generated, if so the apple is generated.
 */
void SnakeLogic::generateApple()
{
    // max amount of apples, or apple can't be generated yet
    if 
    (
        (appleSize == MAX_APPLES) ||
        (movesCount % appleGenerationRate != 0)
    )
    {
        return;
    }

    apples[appleSize] = Apple(rand() % GRID_COLUMNS, rand() % GRID_ROWS);
    appleSize++;
}

/**
 * Checks if snake head is on apple, if so it eats it.
 * 
 * Note, snake growth is delayed by one move. So if snake eat apple this 
 * move, then it won't grow till next one.
 */
void SnakeLogic::eatApple()
{
    // Snake at max size
    if (size == MAX_SNAKE_SIZE)
    {
        return;
    }
    
    for (int i = 0; i < appleSize; i++)
    {
        if (snake[0].gx == apples[i].gx && snake[0].gy == apples[i].gy)
        {
            ateAppleLastMove = true; // delayed snake grow

            // Delete apple that was eaten
            for (int j = i; j < appleSize - 1; j++)
            {
                apples[j] = apples[j + 1];
            }
            appleSize--;
        }
    }
}

/**
 * Checks if snake is dead.
 * 
 * Snake is dead if it went out of bounds, or if head is on top of another snake part.
 * 
 * Note, should be called after every call to move().
 */
bool SnakeLogic::isDead()
{
    // Check if snake ate itself
    for (int i = 1; i < size; i++)
    {
        if (snake[0].gx == snake[i].gx && snake[0].gy == snake[i].gy)
        {
            return true;
        }
    }

    // Check if snake went out of bounds
    if 
    (
        (snake[0].gx < 0 || snake[0].gx >= GRID_COLUMNS) || // zero-index columns & rows
        (snake[0].gy < 0 || snake[0].gy >= GRID_ROWS)
    )
    {
        return true;
    }

    // Snake is alive
    return false;
}

/**
 * Restarts the game. Should use after snake dies.
 */
void SnakeLogic::restart()
{
    snake[0] = SnakePart(1,0);
    snake[1] = SnakePart(0,0);
    size = 2;
    d = Direction::Right;
    appleSize = 0;
    movesCount = 0;
    ateAppleLastMove = false;
}