#include <SFML/Graphics.hpp>

enum class Action
{
    Close_Window, None
};

class SnakeGUI
{
    sf::RenderWindow m_window;
public:

    SnakeGUI();

    bool openWindow();

    bool closeWindow();

    Action getInput() {};
};