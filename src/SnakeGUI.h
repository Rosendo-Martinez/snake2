#include <SFML/Graphics.hpp>

enum class Action
{
    Close_Window, None, Up, Down, Left, Right, Enter_Game
};

enum class Color
{
    Red, Green
};

class SnakeGUI
{
    sf::RenderWindow m_window;
    sf::View m_gameView;
    sf::Font font;

public:

    SnakeGUI();

    bool openWindow();
    
    void clear();
    void drawGrid();
    void drawCell(Color c, int gx, int gy);
    void drawApple(int gx, int gy);
    void drawStartScreen();
    void drawEndScreen();
    void drawScores(int currentScore, int highScore);
    void update();

    Action getInput();
};