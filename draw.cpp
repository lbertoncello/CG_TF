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

    glBegin(GL_POLYGON);
    // glVertex3f(x1, y1, 1.0);

    for (angle = 1.0f; angle < 361.0f; angle += 0.2)
    {
        x2 = x1 + sin(angle) * radius;
        y2 = y1 + cos(angle) * radius;
        glTexCoord2f(cos(angle) * 0.5 + 0.5, sin(angle) * 0.5 + 0.5);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(x2, 0.0, y2);
    }

    glEnd();
}

void Draw::drawFilledCircle2(GLfloat radius, Color color)
{
    //filled circle
    GLfloat x2, y2;
    GLfloat x1 = 0;
    GLfloat y1 = 0;
    GLfloat angle;

    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);

    for (angle = 1.0f; angle < 361.0f; angle += 0.2)
    {
        x2 = x1 + sin(angle) * radius;
        y2 = y1 + cos(angle) * radius;
        glVertex2f(x2, y2);
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
    glVertex3f(p1.getX(), p1.getY(), p1.getZ());
    glVertex3f(p2.getX(), p2.getY(), p2.getZ());
    glVertex3f(p3.getX(), p3.getY(), p3.getZ());
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
    // glutSolidSphere(circle.getRadius(), 30, 30);
    GLfloat r = sphere.getRadius();
    int i, j;
    GLfloat texX = 0.0;
    GLfloat texY0 = 0.0;
    GLfloat texY1 = 0.0;
    GLfloat dTex = 1/30;
    for(i = 0; i <= 30; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / 30);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / 30);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        texY0 = texY1;
        texY1 = (GLfloat)i/30.0;

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= 30; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / 30;
            double x = cos(lng);
            double y = sin(lng);
            texX = (GLfloat) (j / 30.0) + 0.5; 

            glNormal3f(x * zr0, y * zr0, z0);
            glTexCoord2f(texX,texY0);
            glVertex3f(r * x * zr0, 0.25*r * y * zr0, 0.30*r * z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glTexCoord2f(texX,texY1);
            glVertex3f(r * x * zr1, 0.25 * r * y * zr1, 0.30 * r * z1);
        }
        glEnd();
    }
}

void Draw::drawCylinderTube(GLfloat radius, GLfloat height)
{
    GLfloat x = 0.0;
    GLfloat z = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * PI)
    {
        x = radius * cos(angle);
        z = radius * sin(angle);
        glTexCoord2f(angle/(2*PI), 1);
        glVertex3f(x, height, z);
        glTexCoord2f(angle/(2*PI), 0);
        glVertex3f(x, 0.0, z);
        angle = angle + angle_stepsize;
    }
    glTexCoord2f(2 * PI / (2*PI), 1);
    glVertex3f(radius, height, 0.0);
    glTexCoord2f(2 * PI / (2*PI), 0.0);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();
}

void Draw::drawCylinder(GLfloat radius, GLfloat height)
{
    GLfloat x = 0.0;
    GLfloat z = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

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

void Draw::drawParallelSolid(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7, Point p8)
{
    //top
    drawPlane(p1, p2, p3, p4, 0.0, 0.0, 1.0);

    //bottom
    drawPlane(p5, p6, p7, p8, 0.0, 0.0, -1.0);

    //left
    drawPlane(p1, p6, p7, p2, 0.0, 1.0, 0.0);
    
    //right
    drawPlane(p3, p8, p5, p4, 0.0, -1.0, 0.0);

    //back
    drawPlane(p4, p5, p6, p1, 1.0, 0.0, 0.0);

    //front
    drawPlane(p2, p7, p8, p3, -1.0, 0.0, 1.0);
}

void Draw::drawPlane(Point p1, Point p2, Point p3, Point p4, GLfloat normalX, GLfloat normalY, GLfloat normalZ)
{
    glBegin(GL_QUADS);
    glNormal3f(normalX, normalY, normalZ);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(p1.getX(), p1.getY(), p1.getZ());
    glTexCoord2f(0.0, 1.0);
    glVertex3f(p2.getX(), p2.getY(), p2.getZ());
    glTexCoord2f(1.0, 1.0);
    glVertex3f(p3.getX(), p3.getY(), p3.getZ());
    glTexCoord2f(1.0, 0.0);
    glVertex3f(p4.getX(), p4.getY(), p4.getZ());
    glEnd();
}

void Draw::RasterChars(GLfloat x, GLfloat y, GLfloat z, const char * text, double r, double g, double b)
{
    //Push to recover original attributes
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        //Draw text in the x, y, z position
        glColor3f(0,1,0);
        glRasterPos3f(x, y, z);
        const char* tmpStr;
        tmpStr = text;
        while( *tmpStr ){
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *tmpStr);
            tmpStr++;
        }
    glPopAttrib();
}

void Draw::PrintText(GLfloat x, GLfloat y, const char * text, double r, double g, double b)
{
    //Draw text considering a 2D space (disable all 3d features)
    glMatrixMode (GL_PROJECTION);
    //Push to recover original PROJECTION MATRIX
    glPushMatrix();
        glLoadIdentity ();
        glOrtho (0, 1, 0, 1, -1, 1);
        RasterChars(x, y, 0, text, r, g, b);    
    glPopMatrix();
    glMatrixMode (GL_MODELVIEW);
}