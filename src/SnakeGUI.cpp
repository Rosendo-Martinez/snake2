#include "SnakeGUI.h"

SnakeGUI::SnakeGUI() {}

bool SnakeGUI::openWindow()
{
    m_window.create(sf::VideoMode(400, 400), "Snake");
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
}