#ifndef BULLET_H
#define BULLET_H

#include "circle.h"
#include "sphere.h"
#include "draw.h"

class Bullet
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

    GLfloat calcMovement_x(GLfloat deltaIdleTime);
    GLfloat calcMovement_y(GLfloat deltaIdleTime);
    GLfloat calcMovement_z(GLfloat deltaIdleTime);

public:
    Bullet() {}

    Bullet(Sphere body, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngleXY, GLfloat moveAngleYZ)
    {
        this->body = body;
        this->speedNorm = speedNorm;
        this->moveAngleXY = moveAngleXY;
        this->moveAngleYZ = moveAngleYZ;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        this->dZ = moveCoordinates.getZ();

    }

    Bullet(Point bodyCoordinates, GLfloat radius, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngleXY, GLfloat moveAngleYZ, Color color)
    {
        this->body = Sphere(bodyCoordinates, radius, color);
        this->speedNorm = speedNorm;
        this->moveAngleXY = moveAngleXY;
        this->moveAngleYZ = moveAngleYZ;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        this->dZ = moveCoordinates.getZ();
    }

    Bullet(Point bodyCoordinates, GLfloat radius, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngleXY, GLfloat moveAngleYZ)
    {
        this->body = Sphere(bodyCoordinates, radius, Color(1, 0, 1));
        this->speedNorm = speedNorm;
        this->moveAngleXY = moveAngleXY;
        this->moveAngleYZ = moveAngleYZ;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        this->dZ = moveCoordinates.getZ();
        this->startPosition.setX(dX);
        this->startPosition.setY(dY);
        this->startPosition.setZ(dZ);
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

    void draw();
    void move(GLfloat deltaIdleTime);
    Point getCurrentPositionAdjusted();
    Sphere getAdjustedBody();
};

#endif