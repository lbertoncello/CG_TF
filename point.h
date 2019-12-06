#ifndef POINT_H
#define POINT_H

#include <GL/glut.h>

class Point {
    private:
        GLfloat x = 0;
        GLfloat y = 0;
        GLfloat z = 0;
    public:
        Point(GLfloat x, GLfloat y, GLfloat z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Point(GLfloat x, GLfloat y) {
            this->x = x;
            this->y = y;
        }

        Point() {}

        GLfloat getX() {
            return x;
        }

        GLfloat getY() {
            return y;
        }

        GLfloat getZ() {
            return z;
        }

        void setX(GLfloat x) {
            this->x = x;
        }

        void setY(GLfloat y) {
            this->y = y;
        }

        void setZ(GLfloat z) {
            this->z = z;
        }
        
        void update(Point p) {
            this->x = p.getX();
            this->y = p.getY();
            this->z = p.getZ();
        }

        void update(GLfloat x, GLfloat y, GLfloat z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        void update(GLfloat x, GLfloat y) {
            this->x = x;
            this->y = y;
        }
};

#endif