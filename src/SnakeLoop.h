#include "SnakeGUI.h"
#include "SnakeLogic.h"

enum class Scene
{
    In_Game, Start, End
};

class SnakeLoop
{
    SnakeGUI gui;
    SnakeLogic logic;
    bool isRunning = true;
    Direction dir = Direction::Right;
    int currentFrame = 1;
    const int moveRate = 9;
    Scene currentScene = Scene::Start;

    void doUserInput();
    void doGameLogic();
    void doRender();

public:

    SnakeLoop();

    void run();
};