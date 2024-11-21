#include "SnakeScoreTracker.h"

#define INCREMENT 10

SnakeScoreTracker::SnakeScoreTracker()
{
}

int SnakeScoreTracker::getScore()
{
    return score;
}

void SnakeScoreTracker::incrementScore()
{
    score += INCREMENT;
}

void SnakeScoreTracker::resetScore()
{
    score = 0;
}