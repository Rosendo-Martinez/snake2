class SnakeLogic;

/**
 * A class that SnakeLogic can use to keep track of the game scores.
 */
class SnakeScoreTracker
{
    friend class SnakeLogic;

    int score = 0;
    int highestScore = 0;

    void incrementScore();
    void resetScore();

public:
    SnakeScoreTracker();

    int getScore() const;
    int getHighestScore() const;
};