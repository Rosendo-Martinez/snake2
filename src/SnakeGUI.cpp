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
    sf::Color color(255, 255, 255, 50);
    const int gridHeightInCells = windowHeight/cellHeight - 1;
    sf::VertexArray horizontalLines(sf::Lines, gridHeightInCells * 2);

    for (int i = 0; i < gridHeightInCells; i++)
    {
        int firstVertexIndex = i * 2;
        int secondVertexIndex = i * 2 + 1;

        horizontalLines[firstVertexIndex].position = sf::Vector2f(0, cellHeight * (i + 1));
        horizontalLines[secondVertexIndex].position = sf::Vector2f(windowWidth, cellHeight * (i + 1));

        horizontalLines[firstVertexIndex].color = color;
        horizontalLines[secondVertexIndex].color = color;
    }

    const int gridWidthInCells = windowWidth/cellWidth - 1;
    sf::VertexArray verticalLines(sf::Lines, gridWidthInCells * 2);

    for (int i = 0; i < gridWidthInCells; i++)
    {
        int firstVertexIndex = i * 2;
        int secondVertexIndex = i * 2 + 1;

        verticalLines[firstVertexIndex].position = sf::Vector2f(cellWidth * (i + 1), 0);
        verticalLines[secondVertexIndex].position = sf::Vector2f(cellWidth * (i + 1), windowHeight);

        verticalLines[firstVertexIndex].color = color;
        verticalLines[secondVertexIndex].color = color;
    }

    m_window.draw(horizontalLines);
    m_window.draw(verticalLines);
}

/**
 * Draws a cell of the grid a certain color.
 * 
 * Top left cell is origin at (0,0).
 */
void SnakeGUI::drawCell(Color c, int gx, int gy)
{
    sf::Color sfColor;
    if (c == Color::Red)
    {
        sfColor = sf::Color::Red;
    }
    else if (c == Color::Green)
    {
        sfColor = sf::Color::Green;
    }

    sf::RectangleShape square(sf::Vector2f(cellWidth, cellHeight));
    square.setPosition(sf::Vector2f(gx * cellWidth, gy * cellHeight));
    square.setFillColor(sfColor);

    m_window.draw(square);
}

/**
 * Updates the window to display new frame.
 */
void SnakeGUI::update()
{
    m_window.display();
}