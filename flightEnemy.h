#ifndef FLIGHT_ENEMY_H
#define FLIGHT_ENEMY_H

#include <random>
#include <functional>
#include <ctime>
#include <ratio>
#include <chrono>

#include "airplane.h"
#include "draw.h"

#define TURN_LEFT 0
#define TURN_RIGHT 1
#define TURN_UP 2
#define TURN_DOWN 3
#define MOVE_DURATION 3.0

using namespace std::chrono;

class FlightEnemy : public Airplane
{
    Draw drawer;
    GLfloat shotsFrequency;
    high_resolution_clock::time_point lastShotStartTime;
    high_resolution_clock::time_point currentTime;
    high_resolution_clock::time_point lastDirectionChange;
    GLfloat timeToShot = 0;

public:
    FlightEnemy() {}

    FlightEnemy(Sphere body, GLfloat airplaneSpeedMultiplier, GLfloat bulletSpeedMultiplier, GLfloat shotsFrequency) : Airplane(body, airplaneSpeedMultiplier, bulletSpeedMultiplier)
    {
        this->shotsFrequency = shotsFrequency;
        this->timeToShot = 1.0 / shotsFrequency;
    }

    void autoMove(GLfloat deltaIdleTime);
    bool checkAutoMove();
    bool checkAutoShot();
    Bullet* autoShoot(GLfloat deltaIdleTime);
};

#endif