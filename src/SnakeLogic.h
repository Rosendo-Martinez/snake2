
struct SnakePart
{
    int gx, gy;

    SnakePart();
    SnakePart(int gx, int gy);
};

struct Apple
{
    int gx, gy;

    Apple();
    Apple(int gx, int gy);
};

enum class Direction
{
    Left, Right, Up, Down
};

class SnakeLogic
{
    const int MAX_SNAKE_SIZE = 100;
    SnakePart snake[100];
    int size = 2;
    // direction snake is moving
    Direction d;
    const int MAX_APPLE_SIZE = 3;
    Apple apples[3];
    int appleSize = 0;
    int movesCount = 0;
    int appleGenerationRate = 15; // 1 apple ever 5 moves by snake
    bool ateAppleLastMove = false;
    int GRID_ROWS = 20;
    int GRID_COLUMNS = 20;

    void generateApple();
    void eatApple();

public:

    SnakeLogic();

    void move(Direction d);
    bool isDead();
    void restart();

    const SnakePart * getSnake();
    const int getSize();
    const Apple * getApples();
    const int getSizeApples();
};