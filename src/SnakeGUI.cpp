#include "SnakeGUI.h"
#include <iostream>
#include <string>
#include <sstream>

#define GRID_WIDTH  800
#define GRID_HEIGHT 800
#define CELL_WIDTH  40
#define CELL_HEIGHT 40

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
    font.loadFromFile("./assets/font.TTF"); // maybe do error checking?

    m_window.create(sf::VideoMode(GRID_WIDTH, GRID_HEIGHT + CELL_HEIGHT), "Snake");
    m_window.setFramerateLimit(FPS);
    m_window.setKeyRepeatEnabled(false);
    m_gameView.setSize(sf::Vector2f(GRID_WIDTH, GRID_HEIGHT + CELL_HEIGHT));
    m_gameView.setCenter(sf::Vector2f(GRID_WIDTH/2, (GRID_HEIGHT + CELL_HEIGHT)/2));
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
        else if (event.key.code == sf::Keyboard::Space)
        {
            return Action::Toggle_Pause;
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
        if (size.y > GRID_HEIGHT + CELL_HEIGHT)
        {
            // Center grid vertically, and maintain constent height
            newGameViewPort.height = (float) (GRID_HEIGHT + CELL_HEIGHT)/size.y;
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
        hLines[i * 2].position = sf::Vector2f(0, CELL_HEIGHT * (i + 2));
        hLines[i * 2 + 1].position = sf::Vector2f(GRID_WIDTH, CELL_HEIGHT * (i + 2));

        hLines[i * 2].color = GRID_COLOR;
        hLines[i * 2 + 1].color = GRID_COLOR;
    }

    const int vLinesCount = GRID_WIDTH/CELL_WIDTH - 1;
    sf::VertexArray vLines(sf::Lines, vLinesCount * 2);

    for (int i = 0; i < vLinesCount; i++)
    {
        vLines[i * 2].position = sf::Vector2f(CELL_WIDTH * (i + 1), CELL_HEIGHT);
        vLines[i * 2 + 1].position = sf::Vector2f(CELL_WIDTH * (i + 1), GRID_HEIGHT + CELL_HEIGHT);

        vLines[i * 2].color = GRID_COLOR;
        vLines[i * 2 + 1].color = GRID_COLOR;
    }

    m_window.draw(hLines);
    m_window.draw(vLines);

    // draw boarder

    sf::VertexArray boarder(sf::LineStrip, 5);

    boarder[0].position = sf::Vector2f(1, CELL_HEIGHT);
    boarder[1].position = sf::Vector2f(GRID_WIDTH, CELL_HEIGHT);
    boarder[2].position = sf::Vector2f(GRID_WIDTH, GRID_HEIGHT + CELL_HEIGHT);
    boarder[3].position = sf::Vector2f(1, GRID_HEIGHT + CELL_HEIGHT);
    boarder[4].position = sf::Vector2f(1, CELL_HEIGHT);

    boarder[0].color = RED;
    boarder[1].color = RED;
    boarder[2].color = RED;
    boarder[3].color = RED;
    boarder[4].color = RED;

    m_window.draw(boarder);
}

/**
 * Draws a snake part.
 * 
 * Top left cell is origin at (0,0).
 */
void SnakeGUI::drawSnakePart(int gx, int gy)
{
    gy++; // grid offset

    sf::RectangleShape cell(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
    cell.setPosition(sf::Vector2f(gx * CELL_WIDTH, gy * CELL_HEIGHT));
    cell.setFillColor(RED);
    m_window.draw(cell);
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
    gy++; // grid offset

    sf::ConvexShape apple;

    apple.setPointCount(4);
    apple.setPoint(0, sf::Vector2f(5,10));
    apple.setPoint(1, sf::Vector2f(35,10));
    apple.setPoint(2, sf::Vector2f(35,35));
    apple.setPoint(3, sf::Vector2f(5,35));

    apple.setFillColor(GREEN);
    apple.setPosition(sf::Vector2f(gx*CELL_WIDTH, gy*CELL_HEIGHT));

    sf::ConvexShape stem;
    sf::Color brown(139, 69, 19);

    stem.setPointCount(4);
    stem.setPoint(0, sf::Vector2f(20,10));
    stem.setPoint(1, sf::Vector2f(30,0));
    stem.setPoint(2, sf::Vector2f(35,0));
    stem.setPoint(3, sf::Vector2f(25,10));
    stem.setFillColor(brown);
    stem.setPosition(sf::Vector2f(gx*CELL_WIDTH, gy*CELL_HEIGHT));

    m_window.draw(apple);
    m_window.draw(stem);
}

void SnakeGUI::drawScores(int currentScore, int highScore)
{
    sf::Text currentScoreText;
    currentScoreText.setFont(font);
    currentScoreText.setCharacterSize(30);
    currentScoreText.setFillColor(RED);
    currentScoreText.setPosition(sf::Vector2f(0,0));

    std::stringstream currentScoreSS;
    currentScoreSS << "Score  " << currentScore;

    currentScoreText.setString(currentScoreSS.str());

    m_window.draw(currentScoreText);

    sf::Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(30);
    highScoreText.setFillColor(RED);

    std::stringstream highScoreSS;
    highScoreSS << "High  Score  " << highScore;

    highScoreText.setString(highScoreSS.str());

    highScoreText.setPosition(sf::Vector2f(GRID_WIDTH - highScoreText.getGlobalBounds().width,0));
    m_window.draw(highScoreText);
}

void SnakeGUI::drawInstructions(bool iGameOver, bool isPaused)
{
    sf::Text instruction;
    instruction.setFont(font);
    instruction.setCharacterSize(20);
    instruction.setFillColor(RED);
    if (iGameOver) // game over / hasn't started
    {
        instruction.setString("Press  Enter  To  Play");
    }
    else if (!iGameOver && isPaused)
    {
        instruction.setString("Press  Space  To  Unpause");
    }
    else // in game but not paused
    {
        instruction.setString("Press  Space  To  Pause");
    }

    instruction.setPosition(sf::Vector2f(GRID_WIDTH/2 - instruction.getGlobalBounds().width/2,10));
    m_window.draw(instruction);
}