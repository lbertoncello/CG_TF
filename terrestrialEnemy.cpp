#include "terrestrialEnemy.h"

void TerrestrialEnemy::draw()
{
    if (!isDestroyed())
    {
        glPushMatrix();
        glTranslatef(dX, -dY, 0.0);
        // drawer.drawFilledSphere(this->getBody());
        GLfloat mat_ambient_color1[] = {0.7, 0.3, 0.5, 1.0};
        GLfloat mat_ambient_color2[] = {0.3, 0.45, 0.2, 1.0};

        glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_color1);
        // drawer.drawRectangle2(body.getRadius() * 1.44, body.getRadius() * 1.44, body.getColor());

        glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_color2);
        // drawer.drawFilledSphere(body.getRadius() * 0.7, Color(0.3, 0.45, 0.7));
        glutSolidSphere(body.getRadius(), 100, 100);
        glPopMatrix();
    }
}

Point TerrestrialEnemy::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() - startPosition.getX() + dX);
    currentPositionAdjusted.setY(this->body.getCenter_y() - startPosition.getY() + dY);

    return currentPositionAdjusted;
}

Sphere TerrestrialEnemy::getAdjustedBody()
{
    return Sphere(this->getCurrentPositionAdjusted(), this->body.getRadius());
}

void TerrestrialEnemy::reset() {
    destroyed = false;
}