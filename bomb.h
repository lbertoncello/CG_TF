#ifndef BOMB_H
#define BOMB_H

#include <ctime>
#include <ratio>
#include <chrono>

#include "circle.h"
#include "draw.h"
#include "calc.h"

using namespace std::chrono;
using namespace std;

#define BOMB_LIFETIME 2.0

class Bomb
{
    Sphere body;
    GLfloat dX;
    GLfloat dY;
    GLfloat dZ;
    GLfloat speedNorm;
    GLfloat moveAngleXY;
    GLfloat moveAngleYZ;
    Point startPosition;
    Draw drawer;
    Calc calc;
    GLfloat initialRadius;
    GLfloat sizeDecreaseAcceleration;
    high_resolution_clock::time_point dropStartTime;
    high_resolution_clock::time_point currentTime;
    bool onTheGround = false;

    void calcSizeDecreaseAcceleration();
    GLfloat calcCurrentRadiusVariation();
    GLfloat calcMovement_x(GLfloat deltaIdleTime);
    GLfloat calcMovement_y(GLfloat deltaIdleTime);
    GLfloat calcMovement_z(GLfloat deltaIdleTime);

public:
    Bomb() {}

    Bomb(Sphere body, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngleXY, GLfloat moveAngleYZ)
    {
        this->body = body;
        this->speedNorm = speedNorm;
        this->moveAngleXY = moveAngleXY;
        this->moveAngleYZ = moveAngleYZ;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        this->dZ = moveCoordinates.getZ();
        dropStartTime = std::chrono::high_resolution_clock::now();
        currentTime = std::chrono::high_resolution_clock::now();
        initialRadius = this->body.getRadius();
        // calcSizeDecreaseAcceleration();
    }

    Bomb(Point bodyCoordinates, GLfloat radius, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngleXY, GLfloat moveAngleYZ, Color color)
    {
        this->body = Sphere(bodyCoordinates, radius, color);
        this->speedNorm = speedNorm;
        this->moveAngleXY = moveAngleXY;
        this->moveAngleYZ = moveAngleYZ;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        this->dZ = moveCoordinates.getZ();
        dropStartTime = std::chrono::high_resolution_clock::now();
        currentTime = std::chrono::high_resolution_clock::now();
        initialRadius = this->body.getRadius();
        // calcSizeDecreaseAcceleration();
    }

    Bomb(Point bodyCoordinates, GLfloat radius, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngleXY, GLfloat moveAngleYZ)
    {
        this->body = Sphere(bodyCoordinates, radius, Color(0.65, 0.2, 0.45));
        this->speedNorm = speedNorm;
        this->moveAngleXY = moveAngleXY;
        this->moveAngleYZ = moveAngleYZ;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        this->dZ = moveCoordinates.getZ();
        this->startPosition.setX(dX);
        this->startPosition.setY(dY);
        this->startPosition.setZ(dZ);
        dropStartTime = std::chrono::high_resolution_clock::now();
        currentTime = std::chrono::high_resolution_clock::now();
        initialRadius = this->body.getRadius();
        // calcSizeDecreaseAcceleration();
    }

    Sphere &getBody()
    {
        return body;
    }

    GLfloat getSpeed()
    {
        return speedNorm;
    }

    GLfloat getspeedAngle()
    {
        return moveAngleXY;
    }

    bool isOnTheGround()
    {
        return this->dZ <= 0;
    }

    void draw(bool isNightMode);
    void move(GLfloat deltaIdleTime);
    void updateSize();
    Point getCurrentPositionAdjusted();
    Sphere getAdjustedBody();
};

#endif