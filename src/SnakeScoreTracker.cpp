#include "SnakeScoreTracker.h"

#define INCREMENT 10

SnakeScoreTracker::SnakeScoreTracker()
{
}

int SnakeScoreTracker::getScore()
{
    return score;
}

int SnakeScoreTracker::getHighestScore()
{
    return highestScore;
}

bool SnakeScoreTracker::isNewHighScore()
{
    return score > highestScore;
}

void SnakeScoreTracker::incrementScore()
{
    score += INCREMENT;
}

void SnakeScoreTracker::resetScore()
{
    if (score > highestScore)
    {
        highestScore = score;
    }

    score = 0;
}