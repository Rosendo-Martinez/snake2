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

    void doUserInput();
    void doGameLogic();

public:

    SnakeLoop();

    void run();
};