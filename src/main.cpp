#include "SnakeGUI.h"

int main() 
{
    SnakeGUI gui;
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

            input = gui.getInput();
        }

        gui.clear();
        gui.drawGrid();
        gui.drawCell(Color::Red, 0,0);
        gui.drawCell(Color::Red, 10,10);
        gui.update();
    }

    return 0;
}