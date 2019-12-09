#include "terrestrialEnemy.h"

void TerrestrialEnemy::draw(GLuint TerrestrialEnemiesTexture)
{
    if (!isDestroyed())
    {
        glPushMatrix();
        glTranslatef(dX, -dY, 0.0);

        GLfloat mat_emission[] = {0.0, 0.0, 0.0, 0.0};
        GLfloat mat_ambient[] = {0.2, 0.2*140.0/255.0, 0.0, 1.0};
        GLfloat mat_diffuse[] = {0.8, 0.8*140.0/255.0, 0.0, 1.0};
        GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};

        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

        // drawer.drawFilledSphere(this->getBody());
        // drawer.drawRectangle2(body.getRadius() * 1.44, body.getRadius() * 1.44, body.getColor());

        // glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
        // glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
        // glBindTexture(GL_TEXTURE_2D, TerrestrialEnemiesTexture);
        // drawer.drawFilledSphere(body.getRadius() * 0.7, Color(0.3, 0.45, 0.7));
        glutSolidSphere(body.getRadius(), 100, 100);
        glPopMatrix();
    }
}

Point TerrestrialEnemy::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    // currentPositionAdjusted.setX(this->body.getCenter_x() - startPosition.getX() + dX);
    // currentPositionAdjusted.setY(this->body.getCenter_y() - startPosition.getY() + dY);
    currentPositionAdjusted.setX(this->body.getCenter_x() + dX - this->startPosition.getX());
    currentPositionAdjusted.setY(this->body.getCenter_y() + dY - this->startPosition.getY());
    currentPositionAdjusted.setZ(0);

    return currentPositionAdjusted;
}

Sphere TerrestrialEnemy::getAdjustedBody()
{
    return Sphere(this->getCurrentPositionAdjusted(), this->body.getRadius());
}

void TerrestrialEnemy::reset()
{
    destroyed = false;
}