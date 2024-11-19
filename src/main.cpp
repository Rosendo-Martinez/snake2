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

            input = gui.getInput();
        }

        gui.clear();
        gui.drawGrid();
        
        for (int i = 0; i < logic.getSize(); i++)
        {
            gui.drawCell(Color::Red, logic.getSnake()[i].gx, logic.getSnake()[i].gy);
        }

        gui.update();
    }

    return 0;
}