#include "SnakeGUI.h"
#include "SnakeLogic.h"

class SnakeLoop
{
    SnakeGUI gui;
    SnakeLogic logic;
    bool isRunning = true;
    Direction dir = Direction::Right;
    int currentFrame = 1;
    const int moveRate = 9;
    bool isOnStartMenu = true;

    void doUserInput();
    void doGameLogic();
    void doRender();

public:

    SnakeLoop();

    void run();
};