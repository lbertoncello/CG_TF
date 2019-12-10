#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <GL/glut.h>

#include "point.h"
#include "color.h"

class Sphere
{
    GLint id;
    Point center;
    GLfloat radius;
    Color color;
    bool moving = false;
    bool terrestrial = false;
    bool mainSphere = false;

public:
    Sphere() {}

    Sphere(Point center, GLfloat radius)
    {
        this->center = center;
        this->radius = radius;
    }

    Sphere(Point center, GLfloat radius, Color color)
    {
        this->center = center;
        this->radius = radius;
        this->color = color;
    }

    Sphere(GLint id, Point center, GLfloat radius)
    {
        this->id = id;
        this->center = center;
        this->radius = radius;
    }

    Sphere(GLfloat center_x, GLfloat center_y, GLfloat radius)
    {
        this->center.setX(center_x);
        this->center.setY(center_y);
        this->radius = radius;
    }

    Sphere(GLint id, GLfloat center_x, GLfloat center_y, GLfloat radius)
    {
        this->id = id;
        this->center.setX(center_x);
        this->center.setY(center_y);
        this->radius = radius;
    }

    GLint getId()
    {
        return id;
    }

    Point getCenter()
    {
        return center;
    }

    GLfloat getCenter_x()
    {
        return center.getX();
    }

    GLfloat getCenter_y()
    {
        return center.getY();
    }

    GLfloat getCenter_z()
    {
        return center.getZ();
    }

    GLfloat getRadius()
    {
        return radius;
    }

    Color &getColor()
    {
        return color;
    }

    bool isMoving()
    {
        return moving;
    }

    bool isTerrestrial()
    {
        return terrestrial;
    }

    bool isMainSphere()
    {
        return mainSphere;
    }

    void setId(GLint id)
    {
        this->id = id;
    }

    void setCenter_x(GLfloat center_x)
    {
        this->center.setX(center_x);
    }

    void setCenter_y(GLfloat center_y)
    {
        this->center.setY(center_y);
    }

    void setCenter_z(GLfloat center_z)
    {
        this->center.setZ(center_z);
    }

    void setRadius(GLfloat radius)
    {
        this->radius = radius;
    }

    void setColor(Color color)
    {
        this->color = color;
    }

    void setMoving(bool moving)
    {
        this->moving = moving;
    }

    void setTerrestrial(bool terrestrial)
    {
        this->terrestrial = terrestrial;
    }

    void setMainSphere(bool mainSphere)
    {
        this->mainSphere = mainSphere;
    }

    void updateCenter(Point p)
    {
        this->center.setX(p.getX());
        this->center.setY(p.getY());
    }

    void updateCenter(GLfloat x, GLfloat y)
    {
        this->center.setX(x);
        this->center.setY(y);
    }

    bool isPointInSphere(Point p);
    bool isPointInSphere(GLfloat x, GLfloat y, GLfloat z);
    bool checkIntersection(Sphere Sphere, GLint num_segments);
    bool checkIntersection(Sphere Sphere);
    bool isInside(Sphere Sphere, GLint num_segments);
};

#endif