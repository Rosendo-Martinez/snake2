#include "SnakeGUI.h"

SnakeGUI::SnakeGUI() {}

bool SnakeGUI::openWindow()
{
    m_window.create(sf::VideoMode(windowWidth, windowHeight), "Snake");
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

/**
 * Clears the window.
 */
void SnakeGUI::clear()
{
    m_window.clear();
}

/**
 * Draws the grid.
 */
void SnakeGUI::drawGrid()
{
    sf::VertexArray horizontalLines(sf::Lines, 50 * 2);

    const int gridHeightInCells = windowHeight/cellHeight;

    for (int i = 0; i < gridHeightInCells; i++)
    {
        int firstVertexIndex = i * 2;
        int secondVertexIndex = i * 2 + 1;

        horizontalLines[firstVertexIndex].position = sf::Vector2f(0, cellHeight * (i + 1));
        horizontalLines[secondVertexIndex].position = sf::Vector2f(windowWidth, cellHeight * (i + 1));

        horizontalLines[firstVertexIndex].color = sf::Color::White;
        horizontalLines[secondVertexIndex].color = sf::Color::White;
    }

    m_window.draw(horizontalLines);
}

/**
 * Updates the window to display new frame.
 */
void SnakeGUI::update()
{
    m_window.display();
}