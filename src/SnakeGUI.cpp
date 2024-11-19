#include "SnakeGUI.h"

SnakeGUI::SnakeGUI() {}

bool SnakeGUI::openWindow()
{
    m_window.create(sf::VideoMode(400, 400), "Snake");
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
}

/**
 * Gets user input.
 * 
 * Returns None when their is no more user input.
 */
Action SnakeGUI::getInput()
{
    sf::Event event;

    m_window.pollEvent(event);
    
    if (event.type == sf::Event::Closed)
    {
        return Action::Close_Window;
    }

    return Action::None;
}