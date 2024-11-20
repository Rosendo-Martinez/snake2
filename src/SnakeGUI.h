#include <SFML/Graphics.hpp>

#define GRID_WIDTH  800
#define GRID_HEIGHT 800
#define CELL_WIDTH  40
#define CELL_HEIGHT 40

enum class Action
{
    Close_Window, None, Up, Down, Left, Right
};

enum class Color
{
    Red, Green
};

class SnakeGUI
{
    sf::RenderWindow m_window;
public:

    SnakeGUI();

    bool openWindow();
    
    void clear();
    void drawGrid();
    void drawCell(Color c, int gx, int gy);
    void update();

    Action getInput();
};