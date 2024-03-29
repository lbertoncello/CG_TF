#ifndef DRAW_H
#define DRAW_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "circle.h"
#include "sphere.h"
#include "line.h"

using namespace std;

class Draw
{
private:
    GLfloat PI = 3.14159;
    GLint num_segments = 300;
    GLfloat radius = 0.1;

    Point currentCenter;
    vector<Circle> circles;
    vector<Circle>::iterator circle_it;
    vector<Line> lines;
    vector<Line>::iterator line_it;
    Circle *currentCircleMoving = NULL;

    void drawCircle(GLfloat cx, GLfloat cy, GLfloat r, GLint num_segments, Color color);
    void drawEllipse(GLfloat rx, GLfloat ry, Color color, GLint num_segments);

public:
    Draw() {}

    GLint getNumSegments()
    {
        return num_segments;
    }

    GLfloat getRadius()
    {
        return radius;
    }

    Point &getCurrentCenter()
    {
        return currentCenter;
    }

    Circle *getCurrentCircleMoving()
    {
        currentCircleMoving;
    }

    void setRadius(GLfloat radius)
    {
        this->radius = radius;
    }

    void setCurrentCircleMoving(Circle *circle)
    {
        this->currentCircleMoving = circle;
    }

    void addCircle(Circle circle)
    {
        circles.push_back(circle);
    }

    void addLine(Line line)
    {
        lines.push_back(line);
    }

    void addCircleAtCurrentCenter();
    bool thereIsCircleMoving();
    void updateCurrentCircleMoving();
    void updateCurrentCenter(GLfloat x, GLfloat y, GLfloat x_window_size, GLfloat y_window_size);
    bool checkIntersection(Circle circle);
    void drawCircle(Color color);
    void drawCircle(Circle circle);
    void drawEllipse(Circle circle);
    void drawEllipse(GLfloat radius, Color color);
    void drawRectangle(GLfloat width, GLfloat height, Color color);
    void drawRectangle2(GLfloat width, GLfloat height, Color color);
    void drawRectangle(Point p1, Point p2, Point p3, Point p4, Color color);
    void drawTriangle(Point p1, Point p2, Point p3, Color color);
    void drawFilledCircle(GLfloat radius, Color color);
    void drawFilledCircle(Color color);
    void drawFilledCircle(Circle circle);
    void drawFilledCircle2(GLfloat radius, Color color);
    void drawAllCircles(Color color);
    void drawAllCircles();
    void drawLine(Line line);
    void drawLine(Point p1, Point p2, Color color);
    void drawText(string text, Point position);
    void drawAllLines();
    void drawGame();
    void chooseCircleToMove();
    void drawEllipsoid(Sphere sphere);
    void drawCylinderTube(GLfloat radius, GLfloat height);
    void drawCylinder(GLfloat radius, GLfloat height);
    void drawSphere(Sphere sphere);
    void drawParallelSolid(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7, Point p8);
    void drawPlane(Point p1, Point p2, Point p3, Point p4, GLfloat normalX, GLfloat normalY, GLfloat normalZ);
    void PrintText(GLfloat x, GLfloat y, const char * text, double r, double g, double b);
    void RasterChars(GLfloat x, GLfloat y, GLfloat z, const char * text, double r, double g, double b);
};

#endif