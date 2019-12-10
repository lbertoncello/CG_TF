#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>

#include "sphere.h"

using namespace std;

bool Sphere::isPointInSphere(Point p)
{
    GLfloat d = sqrt(pow((p.getX() - center.getX()), 2) + pow((p.getY() - center.getY()), 2) + pow((p.getZ() - center.getZ()), 2));

    if (d > radius)
    {
        return false;
    }

    return true;
}

bool Sphere::isPointInSphere(GLfloat x, GLfloat y, GLfloat z)
{
    return isPointInSphere(Point(x, y, z));
}

// bool Sphere::checkIntersection(Sphere Sphere, GLint num_segments)
// {
//     for (GLint ii = 0; ii < num_segments; ii++)
//     {
//         GLfloat theta = 2.0f * 3.1415926f * GLfloat(ii) / GLfloat(num_segments); //get the current angle

//         GLfloat x = Sphere.getRadius() * cosf(theta) + Sphere.getCenter_x(); //calculate the x component
//         GLfloat y = Sphere.getRadius() * sinf(theta) + Sphere.getCenter_y(); //calculate the y component

//         if (isPointInSphere(x, y, z))
//         {
//             return true;
//         }
//     }

//     return false;
// }

bool Sphere::checkIntersection(Sphere sphere, GLint num_segments)
{
    float r0sqr = sphere.radius * sphere.radius;
    float r1sqr = this->radius * this->radius;

    // float r0sqr = sphere.radius;
    // float r1sqr = this->radius;

    float distX = sphere.getCenter_x() - this->getCenter_x();
    float distY = sphere.getCenter_y() - this->getCenter_y();
    float distZ = sphere.getCenter_z() - this->getCenter_z();

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

bool Sphere::checkIntersection(Sphere Sphere)
{
    return this->checkIntersection(Sphere, 100);
}

// //Verifica se o circulo Sphere está dentro deste
// bool Sphere::isInside(Sphere Sphere, GLint num_segments)
// {
//     for (GLint ii = 0; ii < num_segments; ii++)
//     {
//         GLfloat theta = 2.0f * 3.1415926f * GLfloat(ii) / GLfloat(num_segments); //get the current angle

//         GLfloat x = Sphere.getRadius() * cosf(theta) + Sphere.getCenter_x(); //calculate the x component
//         GLfloat y = Sphere.getRadius() * sinf(theta) + Sphere.getCenter_y(); //calculate the y component

//         if (isPointInSphere(x, y) == false)
//         {
//             return false;
//         }
//     }

//     return true;
// }

bool Sphere::isInside(Sphere sphere, GLint num_segments)
{
    checkIntersection(sphere);

    // float r0sqr = sphere.radius * sphere.radius;
    // float r1sqr = this->radius * this->radius;

    // float distX = sphere.getCenter_x() - this->getCenter_x();
    // float distY = sphere.getCenter_y() - this->getCenter_y();
    // float distZ = sphere.getCenter_z() - this->getCenter_z();

    // // Since we already need to square these, we won't need to take the absolute value
    // // to accurately compare them to the radii
    // distX *= distX;
    // distY *= distY;
    // distZ *= distZ; 

    // float sqrDist = (distX + distY + distZ);

    // if ((r0sqr + r1sqr) < sqrDist)
    // {
    //     return true;
    // }

    // return false;
}