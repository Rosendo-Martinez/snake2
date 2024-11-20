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
        doGameLogic();
        doRender();

        currentFrame++;
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
        else if (input == Action::Right)
        {
            dir = Direction::Right;
        }
        else if (input == Action::Left)
        {
            dir = Direction::Left;
        }
        else if (input == Action::Up)
        {
            dir = Direction::Up;
        }
        else if (input == Action::Down)
        {
            dir = Direction::Down;
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
        logic.move(dir);

        // Restart game if snake died
        if (logic.isDead())
        {
            logic.restart();
            dir = Direction::Right;
            currentFrame = 1;
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
    
    // Draw apples
    for (int i = 0; i < logic.getSizeApples(); i++)
    {
        gui.drawCell(Color::Green, logic.getApples()[i].gx, logic.getApples()[i].gy);
    }

    // Draw snake
    for (int i = 0; i < logic.getSize(); i++)
    {
        gui.drawCell(Color::Red, logic.getSnake()[i].gx, logic.getSnake()[i].gy);
    }

    gui.update();
}