#include "SnakeGUI.h"
#include "SnakeLogic.h"

int main() 
{
    SnakeGUI gui;
    SnakeLogic logic;
    gui.openWindow();
    bool isRunning = true;

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
                logic.move(Direction::Right);
            }
            else if (input == Action::Left)
            {
                logic.move(Direction::Left);
            }
            else if (input == Action::Up)
            {
                logic.move(Direction::Up);
            }
            else if (input == Action::Down)
            {
                logic.move(Direction::Down);
            }

            input = gui.getInput();
        }

        if (logic.isDead())
        {
            return 0;
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
    }

    return 0;
}