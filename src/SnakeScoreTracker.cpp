#include "SnakeScoreTracker.h"

#define INCREMENT 10

SnakeScoreTracker::SnakeScoreTracker()
{
}

/**
 * The score for the current game.
 * 
 * Running score while snake has not died, and final score after snake dies.
 */
int SnakeScoreTracker::getScore()
{
    return score;
}

/**
 * Returns the highest score so far.
 * 
 * Note: does not include the score for current game, even
 * if it is a new high score.
 */
int SnakeScoreTracker::getHighestScore()
{
    return highestScore;
}

/**
 * Checks if the current game score is a 
 * new high score.
 */
bool SnakeScoreTracker::isNewHighScore()
{
    return score > highestScore;
}

/**
 * Call after snake ate apple.
 */
void SnakeScoreTracker::incrementScore()
{
    score += INCREMENT;
}

/**
 * Resets current game score, and 
 * updates highest score if user got a 
 * new high score.
 */
void SnakeScoreTracker::resetScore()
{
    if (score > highestScore)
    {
        highestScore = score;
    }

    score = 0;
}