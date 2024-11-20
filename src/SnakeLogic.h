#define MAX_SNAKE_SIZE 100
#define MAX_APPLES 3

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
    SnakePart snake[MAX_SNAKE_SIZE];
    int size = 2;
    // direction snake is moving
    Direction d;
    Apple apples[MAX_APPLES];
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