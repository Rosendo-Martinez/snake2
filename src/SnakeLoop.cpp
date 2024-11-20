#include "SnakeLoop.h"
#include "SnakeGUI.h"
#include "SnakeLogic.h"

SnakeLoop::SnakeLoop()
{
}

void SnakeLoop::run()
{
    SnakeGUI gui;
    SnakeLogic logic;
    gui.openWindow();
    bool isRunning = true;
    Direction dir = Direction::Right;

    int currentFrame = 1;
    const int moveRate = 9;

    while (isRunning) 
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

        if (currentFrame % moveRate == 0)
        {
            logic.move(dir);
        }

        if (logic.isDead())
        {
            return;
        }

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