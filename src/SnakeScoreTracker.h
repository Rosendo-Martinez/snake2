class SnakeLogic;

class SnakeScoreTracker
{
    friend class SnakeLogic;

    int score = 0;

    void incrementScore();
    void resetScore();

public:
    SnakeScoreTracker();

    int getScore();
};