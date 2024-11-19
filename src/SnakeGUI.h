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
    const int m_windowWidth = 800;
    const int m_windowHeight = 800;
    const int m_cellWidth = 40;
    const int m_cellHeight = 40;
public:

    SnakeGUI();

    SnakeGUI(int windowWidth, int windowHeight, int cellWidth, int cellHeight);

    bool openWindow();
    
    void clear();
    void drawGrid();
    void drawCell(Color c, int gx, int gy);
    void update();

    Action getInput();
};