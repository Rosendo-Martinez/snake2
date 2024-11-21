#include "SnakeGUI.h"
#include <iostream>

#define RED sf::Color(255, 0, 0, 255)
#define GREEN sf::Color(0, 255, 0, 255)
#define GRID_COLOR sf::Color(255, 255, 255, 30)
#define FPS 60

/**
 * Snake GUI with default window size and cell size.
 */
SnakeGUI::SnakeGUI() {}

/**
 * Creates, initializes, and opens the window.
 */
bool SnakeGUI::openWindow()
{
    m_window.create(sf::VideoMode(GRID_WIDTH, GRID_HEIGHT), "Snake");
    m_window.setFramerateLimit(FPS);
    m_window.setKeyRepeatEnabled(false);
    m_gameView.setSize(sf::Vector2f(GRID_WIDTH, GRID_HEIGHT));
    m_gameView.setCenter(sf::Vector2f(GRID_WIDTH/2, GRID_HEIGHT/2));
    m_gameView.setViewport(sf::FloatRect(0,0,1,1));

    m_window.setView(m_gameView);
}

/**
 * Gets user input.
 * 
 * Returns None when their is no more user input.
 */
Action SnakeGUI::getInput()
{
    sf::Event event;

    if (!m_window.pollEvent(event))
    {
        // empty event queue
        return Action::None;
    }

    if (event.type == sf::Event::Closed)
    {
        return Action::Close_Window;
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Right)
        {
            return Action::Right;
        }
        else if (event.key.code == sf::Keyboard::Left)
        {
            return Action::Left;
        }
        else if (event.key.code == sf::Keyboard::Up)
        {
            return Action::Up;
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            return Action::Down;
        }
        else if (event.key.code == sf::Keyboard::Enter)
        {
            return Action::Enter_Game;
        }
    }

    // Handle resizing of screen
    if (event.type == sf::Event::Resized)
    {
        sf::Vector2u size = m_window.getSize();
        sf::FloatRect newGameViewPort(0,0,1,1);

        if (size.x > GRID_WIDTH)
        {
            // Center grid horizontally, and maintain constent width
            newGameViewPort.width = (float) GRID_WIDTH/size.x;
            newGameViewPort.left = (1 - newGameViewPort.width)/2;
        }
        if (size.y > GRID_HEIGHT)
        {
            // Center grid vertically, and maintain constent height
            newGameViewPort.height = (float) GRID_HEIGHT/size.y;
            newGameViewPort.top = (1 - newGameViewPort.height)/2;
        }

        m_gameView.setViewport(newGameViewPort);
        m_window.setView(m_gameView);

        // resizing is handled automatically
        return Action::None;
    }

    // unsupported event
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
    const int hLinesCount = GRID_HEIGHT/CELL_HEIGHT - 1;
    sf::VertexArray hLines(sf::Lines, hLinesCount * 2);

    for (int i = 0; i < hLinesCount; i++)
    {
        hLines[i * 2].position = sf::Vector2f(0, CELL_HEIGHT * (i + 1));
        hLines[i * 2 + 1].position = sf::Vector2f(GRID_WIDTH, CELL_HEIGHT * (i + 1));

        hLines[i * 2].color = GRID_COLOR;
        hLines[i * 2 + 1].color = GRID_COLOR;
    }

    const int vLinesCount = GRID_WIDTH/CELL_WIDTH - 1;
    sf::VertexArray vLines(sf::Lines, vLinesCount * 2);

    for (int i = 0; i < vLinesCount; i++)
    {
        vLines[i * 2].position = sf::Vector2f(CELL_WIDTH * (i + 1), 0);
        vLines[i * 2 + 1].position = sf::Vector2f(CELL_WIDTH * (i + 1), GRID_HEIGHT);

        vLines[i * 2].color = GRID_COLOR;
        vLines[i * 2 + 1].color = GRID_COLOR;
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
        sfColor = RED;
    }
    else if (c == Color::Green)
    {
        sfColor = GREEN;
    }

    sf::RectangleShape cell(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
    cell.setPosition(sf::Vector2f(gx * CELL_WIDTH, gy * CELL_HEIGHT));
    cell.setFillColor(sfColor);
    m_window.draw(cell);
}

/**
 * Draws the start screen.
 */
void SnakeGUI::drawStartScreen()
{
    sf::RectangleShape rectangle(sf::Vector2f(GRID_WIDTH, GRID_HEIGHT));
    rectangle.setFillColor(sf::Color::White);
    m_window.draw(rectangle);
}

/**
 * Draws the end screen.
 */
void SnakeGUI::drawEndScreen()
{
    sf::RectangleShape rectangle(sf::Vector2f(GRID_WIDTH, GRID_HEIGHT));
    rectangle.setFillColor(sf::Color::Blue);
    m_window.draw(rectangle);
}

/**
 * Updates the window to display new frame.
 */
void SnakeGUI::update()
{
    m_window.display();
}

void SnakeGUI::drawApple(int gx, int gy)
{
    sf::ConvexShape apple;

    apple.setPointCount(4);
    apple.setPoint(0, sf::Vector2f(0,0));
    apple.setPoint(1, sf::Vector2f(CELL_WIDTH,0));
    apple.setPoint(2, sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
    apple.setPoint(3, sf::Vector2f(0,CELL_HEIGHT));

    apple.setFillColor(GREEN);
    apple.setPosition(sf::Vector2f(gx*CELL_WIDTH, gy*CELL_HEIGHT));

    m_window.draw(apple);
}