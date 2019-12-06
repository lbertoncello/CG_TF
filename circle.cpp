#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>

#include "circle.h"

using namespace std;

bool Circle::isPointInCircle(Point p)
{
    GLfloat d = sqrt(pow((p.getX() - center.getX()), 2) + pow((p.getY() - center.getY()), 2));

    if (d > radius)
    {
        return false;
    }

    return true;
}

bool Circle::isPointInCircle(GLfloat x, GLfloat y)
{
    return isPointInCircle(Point(x, y));
}

bool Circle::checkIntersection(Circle circle, GLint num_segments)
{
    for (GLint ii = 0; ii < num_segments; ii++)
    {
        GLfloat theta = 2.0f * 3.1415926f * GLfloat(ii) / GLfloat(num_segments); //get the current angle

        GLfloat x = circle.getRadius() * cosf(theta) + circle.getCenter_x(); //calculate the x component
        GLfloat y = circle.getRadius() * sinf(theta) + circle.getCenter_y(); //calculate the y component

        if (isPointInCircle(x, y))
        {
            return true;
        }
    }

    return false;
}

bool Circle::checkIntersection(Circle circle)
{
    return this->checkIntersection(circle, 100);
}

//Verifica se o circulo circle está dentro deste
bool Circle::isInside(Circle circle, GLint num_segments)
{
    for (GLint ii = 0; ii < num_segments; ii++)
    {
        GLfloat theta = 2.0f * 3.1415926f * GLfloat(ii) / GLfloat(num_segments); //get the current angle

        GLfloat x = circle.getRadius() * cosf(theta) + circle.getCenter_x(); //calculate the x component
        GLfloat y = circle.getRadius() * sinf(theta) + circle.getCenter_y(); //calculate the y component

        if (isPointInCircle(x, y) == false)
        {
            return false;
        }
    }

    return true;
}

bool Circle::checkIntersection(Sphere sphere, GLint num_segments)
{
    float r0sqr = sphere.getRadius() * sphere.getRadius();
    float r1sqr = this->radius * this->radius;

    float distX = sphere.getCenter_x() - this->getCenter_x();
    float distY = sphere.getCenter_y() - this->getCenter_y();
    float distZ = sphere.getCenter_z() - 0;

    // Since we already need to square these, we won't need to take the absolute value
    // to accurately compare them to the radii
    distX *= distX;
    distY *= distY;
    distZ *= distZ;

    float sqrDist = (distX + distY + distZ);

    if ((r0sqr + r1sqr) > sqrDist)
    {
        return true;
    }

    return false;
}