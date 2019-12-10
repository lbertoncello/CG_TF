#ifndef TERRESTRIAL_ENEMY_H
#define TERRESTRIAL_ENEMY_H

#include "enemy.h"
#include "draw.h"

class TerrestrialEnemy
{
private:
    Draw drawer;
    Sphere body;
    Point currentPosition;
    Point startPosition;
    GLfloat dX;
    GLfloat dY;
    bool startPositionInitialized = false;

    bool destroyed = false;

public:
    TerrestrialEnemy() {}

    TerrestrialEnemy(Sphere body)
    {
        this->body = body;
    }

    Sphere &getBody()
    {
        return body;
    }

    Point getCurrentPosition()
    {
        return currentPosition;
    }

    bool isDestroyed()
    {
        return destroyed;
    }

    void setCurrentPosition(Point currentPosition)
    {
        if (startPositionInitialized == false)
        {
            startPosition.setX(currentPosition.getX());
            startPosition.setY(currentPosition.getY());
            startPositionInitialized = true;
        }

        dX = currentPosition.getX();
        dY = currentPosition.getY();

        this->currentPosition = currentPosition;
    }

    void setBody(Sphere body)
    {
        this->body = body;
    }

    void setDestroyed(bool destroyed)
    {
        this->destroyed = destroyed;
    }

    Point getCurrentPositionAdjusted();
    Sphere getAdjustedBody();
    void draw(GLuint TerrestrialEnemiesTexture, bool isNightMode);
    void draw2D();
    void reset();
};

#endif