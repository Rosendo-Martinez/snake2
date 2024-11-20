#include <SFML/Graphics.hpp>

#define GRID_WIDTH  800
#define GRID_HEIGHT 800
#define CELL_WIDTH  40
#define CELL_HEIGHT 40

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
public:

    SnakeGUI();

    bool openWindow();
    
    void clear();
    void drawGrid();
    void drawCell(Color c, int gx, int gy);
    void drawStartScreen();
    void update();

    Action getInput();
};