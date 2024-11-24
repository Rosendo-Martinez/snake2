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

    currentDirection = Direction::Right;

    std::srand(std::time(nullptr)); // use current time as seed for random generator
}

/**
 * Moves the snake.
 * 
 * Note: snake can't move backwards. If user tries to move backwards 
 * the given direction will be ignored, and snake will move forward.
 */
void SnakeLogic::move(Direction dir)
{
    if (ateAppleLastMove)
    {
        // Snake ate apple last move, so it grows this move.
        snakeSize++;
        ateAppleLastMove = false;
    }

    // Ignore direction that moves snake backwards
    if 
    (   
        (this->currentDirection == Direction::Right && dir == Direction::Left) ||
        (this->currentDirection == Direction::Left && dir == Direction::Right) ||
        (this->currentDirection == Direction::Up && dir == Direction::Down)    ||
        (this->currentDirection == Direction::Down && dir == Direction::Up)
    )
    {
        dir = this->currentDirection;
    }

    // shift snake back
    for (int i = snakeSize - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    // Update position of head
    if (dir == Direction::Up)
    {
        snake[0].gy--;
    }
    else if (dir == Direction::Down)
    {
        snake[0].gy++;
    }
    else if (dir == Direction::Left)
    {
        snake[0].gx--;
    }
    else if (dir == Direction::Right)
    {
        snake[0].gx++;
    }

    this->currentDirection = dir;
    movesCount++;
    eatApple();
    generateApple();
}

/**
 * The array of SnakeParts that represent the snake.
 * 
 * The head is at index 0.
 * The tail is at index getSnakeSize() - 1.
 */
const SnakePart * SnakeLogic::getSnake()
{
    return snake;
}

/**
 * The size of the snake.
 */
const int SnakeLogic::getSnakeSize()
{
    return snakeSize;
}

/**
 * The apples that are currently spawned.
 */
const Apple * SnakeLogic::getApples()
{
    return apples;
}

/**
 * The number of apples currently spawned.
 */
const int SnakeLogic::getApplesSize()
{
    return applesSize;
}

/**
 * Checks if apple can be generated, if so the apple is generated.
 */
void SnakeLogic::generateApple()
{
    // max amount of apples, or apple can't be generated yet
    if 
    (
        (applesSize == MAX_APPLES) ||
        (movesCount % appleGenerationRate != 0)
    )
    {
        return;
    }

    apples[applesSize] = Apple(rand() % GRID_COLUMNS, rand() % GRID_ROWS);
    applesSize++;
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
    if (snakeSize == MAX_SNAKE_SIZE)
    {
        return;
    }
    
    for (int i = 0; i < applesSize; i++)
    {
        if (snake[0].gx == apples[i].gx && snake[0].gy == apples[i].gy)
        {
            ateAppleLastMove = true; // delayed snake grow

            // Delete apple that was eaten
            for (int j = i; j < applesSize - 1; j++)
            {
                apples[j] = apples[j + 1];
            }
            applesSize--;
            st.incrementScore();
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
    for (int i = 1; i < snakeSize; i++)
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
 * Restarts the game. Should call right before starting next 
 * game.
 * 
 * Note: score tracker is also reset. Calling this method to soon could cause
 * score tracker to return unexpected results.
 */
void SnakeLogic::restart()
{
    snake[0] = SnakePart(1,0);
    snake[1] = SnakePart(0,0);
    snakeSize = 2;
    currentDirection = Direction::Right;
    applesSize = 0;
    movesCount = 0;
    ateAppleLastMove = false;
    st.resetScore();
}