#include "flightEnemy.h"

void FlightEnemy::autoMove(GLfloat deltaIdleTime)
{

    if (checkAutoMove())
    {
        lastDirectionChange = std::chrono::high_resolution_clock::now();
        std::random_device r;

        auto randomGeneratorX = std::bind(std::uniform_int_distribution<>(0, 3), std::default_random_engine(r()));
        auto randomGeneratorY = std::bind(std::uniform_int_distribution<>(2, 3), std::default_random_engine(r()));

        if (randomGeneratorX() == TURN_LEFT)
        {
            this->setTurningLeft(true);
            this->setTurningRight(false);
        }
        else
        {
            this->setTurningLeft(false);
            this->setTurningRight(true);
        }

        if (randomGeneratorX() == TURN_UP)
        {
            this->setTurningUp(true);
            this->setTurningDown(false);
        }
        else
        {
            this->setTurningUp(false);
            this->setTurningDown(true);
        }
    }

    // switch (randomGenerator())
    // {
    // case TURN_LEFT:
    //     this->setTurningLeft(true);
    //     this->setTurningRight(false);
    //     this->setTurningUp(false);
    //     this->setTurningDown(false);
    //     break;
    // case TURN_RIGHT:
    //     this->setTurningLeft(false);
    //     this->setTurningRight(true);
    //     this->setTurningUp(false);
    //     this->setTurningDown(false);
    //     break;
    // case TURN_UP:
    //     this->setTurningLeft(false);
    //     this->setTurningRight(false);
    //     this->setTurningUp(true);
    //     this->setTurningDown(false);
    //     break;
    // case TURN_DOWN:
    //     this->setTurningLeft(false);
    //     this->setTurningRight(false);
    //     this->setTurningUp(false);
    //     this->setTurningDown(true);
    //     break;
    // }

    this->move(deltaIdleTime);
}

bool FlightEnemy::checkAutoMove()
{
    high_resolution_clock::time_point timeNow = std::chrono::high_resolution_clock::now();
    duration<GLfloat> timeSpan = duration_cast<duration<GLfloat>>(timeNow - lastDirectionChange);
    GLfloat timeElapsed = timeSpan.count();

    if (timeElapsed >= MOVE_DURATION)
    {
        return true;
    }

    return false;
}

bool FlightEnemy::checkAutoShot()
{
    currentTime = std::chrono::high_resolution_clock::now();
    duration<GLfloat> timeSpan = duration_cast<duration<GLfloat>>(currentTime - lastShotStartTime);
    GLfloat lastShotTimeElapsed = timeSpan.count();

    if (lastShotTimeElapsed >= timeToShot)
    {
        return true;
    }

    return false;
}

Bullet *FlightEnemy::autoShoot(GLfloat deltaIdleTime)
{
    lastShotStartTime = std::chrono::high_resolution_clock::now();

    return this->shoot(deltaIdleTime);
}