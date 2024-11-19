
struct SnakePart
{
    int gx, gy;

    SnakePart();
    SnakePart(int gx, int gy);
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

public:

    SnakeLogic();

    void move(Direction d);

    const SnakePart * getSnake();
    const int getSize();
};