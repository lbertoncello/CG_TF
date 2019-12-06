#include "draw.h"

bool Draw::thereIsCircleMoving()
{
    if (currentCircleMoving == NULL)
    {
        return false;
    }

    return true;
}

void Draw::updateCurrentCircleMoving()
{
    currentCircleMoving->updateCenter(currentCenter);
}

void Draw::drawCircle(GLfloat cx, GLfloat cy, GLfloat r, GLint num_segments, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glBegin(GL_LINE_LOOP);

    for (GLint ii = 0; ii < num_segments; ii++)
    {
        GLfloat theta = 2.0f * 3.1415926f * GLfloat(ii) / GLfloat(num_segments); //get the current angle

        GLfloat x = r * cosf(theta); //calculate the x component
        GLfloat y = r * sinf(theta); //calculate the y component

        glVertex3f(x, y, 1.0); //output vertex
    }
    glEnd();
}

void Draw::drawEllipse(GLfloat rx, GLfloat ry, Color color, GLint num_segments)
{
    GLfloat theta = 2 * 3.1415926 / GLfloat(num_segments);
    GLfloat c = cosf(theta); //precalculate the sine and cosine
    GLfloat s = sinf(theta);
    GLfloat t;

    GLfloat x = 1; //we start at angle = 0
    GLfloat y = 0;

    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLE_FAN);
    for (GLint ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset
        glVertex3f(x * rx, y * ry, 1.0); //output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void Draw::drawFilledCircle(GLfloat radius, Color color)
{
    //filled circle
    GLfloat x2, y2;
    GLfloat x1 = 0;
    GLfloat y1 = 0;
    GLfloat angle;

    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x1, y1, 1.0);

    for (angle = 1.0f; angle < 361.0f; angle += 0.2)
    {
        x2 = x1 + sin(angle) * radius;
        y2 = y1 + cos(angle) * radius;
        glVertex3f(x2, y2, 1.0);
    }

    glEnd();
}

void Draw::drawRectangle(Point p1, Point p2, Point p3, Point p4, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glBegin(GL_POLYGON);
    glVertex3f(p1.getX(), p1.getY(), 1.0);
    glVertex3f(p2.getX(), p2.getY(), 1.0);
    glVertex3f(p3.getX(), p3.getY(), 1.0);
    glVertex3f(p4.getX(), p4.getY(), 1.0);
    glEnd();
}

void Draw::drawRectangle(GLfloat width, GLfloat height, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glBegin(GL_QUADS);
    glVertex3f(-width / 2.0, 0, 1.0);
    glVertex3f(width / 2.0, 0, 1.0);
    glVertex3f(width / 2.0, height, 1.0);
    glVertex3f(-width / 2.0, height, 1.0);
    glEnd();
}

void Draw::drawRectangle2(GLfloat width, GLfloat height, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glBegin(GL_QUADS);
    glVertex3f(-width / 2.0, -height / 2.0, 1.0);
    glVertex3f(width / 2.0, -height / 2.0, 1.0);
    glVertex3f(width / 2.0, height / 2.0, 1.0);
    glVertex3f(-width / 2.0, height / 2.0, 1.0);
    glEnd();
}

void Draw::drawTriangle(Point p1, Point p2, Point p3, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLES);
    glVertex3f(p1.getX(), p1.getY(), 1.0);
    glVertex3f(p2.getX(), p2.getY(), 1.0);
    glVertex3f(p3.getX(), p3.getY(), 1.0);
    glEnd();
}

void Draw::updateCurrentCenter(GLfloat x, GLfloat y, GLfloat x_window_size, GLfloat y_window_size)
{
    GLfloat center_x = x;
    GLfloat center_y = y_window_size - y;

    currentCenter.update(center_x, center_y);
}

bool Draw::checkIntersection(Circle circle)
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        if (circle.checkIntersection(*circle_it, num_segments))
        {
            return true;
        }
    }

    return false;
}

void Draw::drawCircle(Circle circle)
{
    drawCircle(circle.getCenter_x(), circle.getCenter_y(), circle.getRadius(), num_segments, circle.getColor());
}

void Draw::drawEllipse(Circle circle)
{
    drawEllipse(circle.getRadius(), circle.getRadius() / 4, circle.getColor(), num_segments);
}

void Draw::drawEllipse(GLfloat radius, Color color)
{
    drawEllipse(radius, radius / 4, color, num_segments);
}

void Draw::drawCircle(Color color)
{
    drawCircle(currentCenter.getX(), currentCenter.getY(), radius, num_segments, color);
}

void Draw::drawFilledCircle(Color color)
{
    drawFilledCircle(radius, color);
}

void Draw::drawFilledCircle(Circle circle)
{
    drawFilledCircle(circle.getRadius(), circle.getColor());
}

void Draw::drawAllCircles(Color color)
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        drawFilledCircle(circle_it->getRadius(), color);
    }
}

void Draw::drawAllCircles()
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        drawFilledCircle(circle_it->getRadius(), circle_it->getColor());
    }
}

void Draw::chooseCircleToMove()
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        if (circle_it->isPointInCircle(currentCenter.getX(), currentCenter.getY()))
        {
            circle_it->setMoving(true);
            currentCircleMoving = &(*circle_it);
            break;
        }
    }
}

void Draw::drawLine(Line line)
{
    glColor3f(line.getColor().getR(), line.getColor().getG(), line.getColor().getB());
    glPointSize(0.5);

    glBegin(GL_LINES);
    glVertex2d(line.getPoint1_x(), line.getPoint1_y());
    glVertex2d(line.getPoint2_x(), line.getPoint2_y());
    glEnd();
}

void Draw::drawLine(Point p1, Point p2, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glPointSize(0.5);

    glBegin(GL_LINES);
    glVertex2d(p1.getX(), p1.getY());
    glVertex2d(p2.getX(), p2.getY());
    glEnd();
}

void Draw::drawAllLines()
{
    for (line_it = lines.begin(); line_it != lines.end(); line_it++)
    {
        drawLine(*line_it);
    }
}

void Draw::drawText(string text, Point position)
{
    glPushMatrix();
    glColor3d(1, 1, 1);
    // glRasterPos3i(200, -270, 0);
    glRasterPos3i(position.getX(), position.getY(), 0);
    for (int i = 0; i < text.length(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, text[i]);
    }
    glPopMatrix();
}

void Draw::drawEllipsoid(Sphere sphere)
{
    glutSolidSphere(sphere.getRadius(), 30, 30);
}

void Draw::drawCylinder(Sphere sphere)
{
    GLfloat radius = sphere.getRadius() * 0.1;
    GLfloat height = sphere.getRadius() * 0.5;
    GLfloat R = 0.0;
    GLfloat G = 0.0;
    GLfloat B = 0.0;

    GLfloat x = 0.0;
    GLfloat z = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    // glColor3ub(R-40,G-40,B-40);
    GLfloat mat_ambient_g[] = {R, G, B, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_g);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * PI)
    {
        x = radius * cos(angle);
        z = radius * sin(angle);
        glVertex3f(x, height, z);
        glVertex3f(x, 0.0, z);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, height, 0.0);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    // glColor3ub(R,G,B);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_g);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * PI)
    {
        x = radius * cos(angle);
        z = radius * sin(angle);
        glVertex3f(x, height, z);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, height, 0.0);
    glEnd();
}

void Draw::drawSphere(Sphere sphere)
{
    glutSolidSphere(sphere.getRadius(), 100, 100);
}