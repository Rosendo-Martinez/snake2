#include "SnakeLoop.h"

SnakeLoop::SnakeLoop()
{
}

void SnakeLoop::run()
{
    gui.openWindow();

    while (isRunning) 
    {
        doUserInput();
        doGameLogic();

        gui.clear();
        gui.drawGrid();
        
        for (int i = 0; i < logic.getSize(); i++)
        {
            gui.drawCell(Color::Red, logic.getSnake()[i].gx, logic.getSnake()[i].gy);
        }

        for (int i = 0; i < logic.getSizeApples(); i++)
        {
            gui.drawCell(Color::Green, logic.getApples()[i].gx, logic.getApples()[i].gy);
        }

        gui.update();

        currentFrame++;
    }
}

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

void SnakeLoop::doGameLogic()
{
    if (currentFrame % moveRate == 0)
    {
        logic.move(dir);
    }

    if (logic.isDead())
    {
        isRunning = false;
    }
}