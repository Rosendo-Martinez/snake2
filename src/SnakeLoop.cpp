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
        if (currentScene == Scene::In_Game)
        {
            doGameLogic();
        }
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
        
        if (currentScene == Scene::In_Game)
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
        } 
        else if (currentScene == Scene::End)
        {
            if (input == Action::Enter_Game)
            {
                // Restart game 
                logic.restart();
                userInputDir = Direction::Right;
                currentFrame = 1;

                currentScene = Scene::In_Game;
            }
        }
        else // start scene
        {
            if (input == Action::Enter_Game)
            {
                currentScene = Scene::In_Game;
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
            currentScene = Scene::End;
        }
    }
}

/**
 * Does rendering to window.
 */
void SnakeLoop::doRender()
{
    gui.clear();

    if (currentScene == Scene::Start)
    {
        gui.drawStartScreen();
    }
    else if (currentScene == Scene::End)
    {
        gui.drawEndScreen();
    }
    else // in game
    {
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
    }

    gui.update();
}