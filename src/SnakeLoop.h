#include "SnakeGUI.h"
#include "SnakeLogic.h"


class SnakeLoop
{
    enum class Scene
    {
        In_Game, Start, End
    };
    
    SnakeGUI gui;
    SnakeLogic logic;
    bool isRunning = true;
    Direction userInputDir = Direction::Right;
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