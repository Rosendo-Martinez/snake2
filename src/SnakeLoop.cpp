#include "SnakeLoop.h"

SnakeLoop::SnakeLoop()
{
}

/**
 * The main game loop.
 */
void SnakeLoop::run()
{
    gui.openWindow();

    while (isRunning) 
    {
        doUserInput();
        if (!isPaused && !isGameOver)
        {
            doGameLogic();
            currentFrame++;
        }
        doRender();
    }
}

/**
 * Handles user input.
 */
void SnakeLoop::doUserInput()
{
    Action input = gui.getInput();
    while (input != Action::None)
    {
        if (input == Action::Close_Window)
        {
            isRunning = false;
            break;
        }
        
        if (isGameOver)
        {
            if (input == Action::Enter_Game)
            {
                // Restart game
                logic.restart();
                userInputDir = Direction::Right;
                currentFrame = 1;
                isPaused = false;
                isGameOver = false;
            }
        }
        else if (!isPaused) // in game
        {
            if (input == Action::Right)
            {
                userInputDir = Direction::Right;
            }
            else if (input == Action::Left)
            {
                userInputDir = Direction::Left;
            }
            else if (input == Action::Up)
            {
                userInputDir = Direction::Up;
            }
            else if (input == Action::Down)
            {
                userInputDir = Direction::Down;
            }
            else if (input == Action::Toggle_Pause)
            {
                isPaused = true;
            }
        }
        else // in game but paused
        {
            if (input == Action::Toggle_Pause)
            {
                isPaused = false;
            }
        }

        input = gui.getInput();
    }   
}

/**
 * Does game logic.
 */
void SnakeLoop::doGameLogic()
{
    if (currentFrame % moveRate == 0)
    {
        // Move snake
        logic.move(userInputDir);

        // Game over, go to end scene
        if (logic.isDead())
        {
            isGameOver = true;
        }
    }
}

/**
 * Does rendering to window.
 */
void SnakeLoop::doRender()
{
    gui.clear();

    gui.drawGrid();
    
    gui.drawScores(logic.st.getScore(), logic.st.getHighestScore());

    // Draw apples
    for (int i = 0; i < logic.getApplesSize(); i++)
    {
        gui.drawApple(logic.getApples()[i].gx, logic.getApples()[i].gy);
    }

    // Draw snake
    for (int i = 0; i < logic.getSnakeSize(); i++)
    {
        gui.drawSnakePart(logic.getSnake()[i].gx, logic.getSnake()[i].gy);
    }

    gui.drawInstructions(isGameOver, isPaused);

    gui.update();
}