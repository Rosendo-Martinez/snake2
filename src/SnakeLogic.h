#define MAX_SNAKE_SIZE 100
#define MAX_APPLES 3
#define GRID_ROWS 20
#define GRID_COLUMNS 20

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
    int snakeSize = 2;
    Direction currentDirection;
    Apple apples[MAX_APPLES];
    int applesSize = 0;
    int movesCount = 0;
    int appleGenerationRate = 15;
    bool ateAppleLastMove = false;
    int applesEaten = 0;

    void generateApple();
    void eatApple();

public:

    SnakeLogic();

    void move(Direction dir);
    bool isDead();
    void restart();

    const SnakePart * getSnake();
    const int getSize();
    const Apple * getApples();
    const int getSizeApples();
    int getApplesEaten();
};