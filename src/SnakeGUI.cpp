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
    sf::Color color(255, 255, 255, 30);
    
    const int hLinesCount = windowHeight/cellHeight - 1;
    sf::VertexArray hLines(sf::Lines, hLinesCount * 2);

    for (int i = 0; i < hLinesCount; i++)
    {
        hLines[i * 2].position = sf::Vector2f(0, cellHeight * (i + 1));
        hLines[i * 2 + 1].position = sf::Vector2f(windowWidth, cellHeight * (i + 1));

        hLines[i * 2].color = color;
        hLines[i * 2 + 1].color = color;
    }

    const int vLinesCount = windowWidth/cellWidth - 1;
    sf::VertexArray vLines(sf::Lines, vLinesCount * 2);

    for (int i = 0; i < vLinesCount; i++)
    {
        vLines[i * 2].position = sf::Vector2f(cellWidth * (i + 1), 0);
        vLines[i * 2 + 1].position = sf::Vector2f(cellWidth * (i + 1), windowHeight);

        vLines[i * 2].color = color;
        vLines[i * 2 + 1].color = color;
    }

    m_window.draw(hLines);
    m_window.draw(vLines);
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

    sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
    cell.setPosition(sf::Vector2f(gx * cellWidth, gy * cellHeight));
    cell.setFillColor(sfColor);
    m_window.draw(cell);
}

/**
 * Updates the window to display new frame.
 */
void SnakeGUI::update()
{
    m_window.display();
}