#include <SFML/Graphics.hpp>

enum class Action
{
    Close_Window, None
};

enum class Color
{
    Red, Green
};

class SnakeGUI
{
    sf::RenderWindow m_window;
    const int windowWidth = 800;
    const int windowHeight = 800;
    const int cellWidth = 40;
    const int cellHeight = 40;
public:

    SnakeGUI();

    bool openWindow();

    void clear();

    void drawGrid();

    void drawCell(Color c, int gx, int gy);

    void update();

    // void drawApple();

    // void drawSnakePart();

    bool closeWindow();

    Action getInput();
};