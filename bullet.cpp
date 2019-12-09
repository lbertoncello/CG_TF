#include "bullet.h"

void Bullet::move(GLfloat deltaIdleTime)
{
    dX += calcMovement_x(deltaIdleTime);
    dY += calcMovement_y(deltaIdleTime);
    dZ += calcMovement_z(deltaIdleTime);
}

GLfloat Bullet::calcMovement_x(GLfloat deltaIdleTime)
{
    // return speedNorm * deltaIdleTime * cos(moveAngle);
    return speedNorm * deltaIdleTime * cos(moveAngleXY) * cos(moveAngleYZ);
}

GLfloat Bullet::calcMovement_y(GLfloat deltaIdleTime)
{
    // return speedNorm * deltaIdleTime * sin(moveAngle);
    return speedNorm * deltaIdleTime * sin(moveAngleXY) * cos(moveAngleYZ);
}

GLfloat Bullet::calcMovement_z(GLfloat deltaIdleTime)
{
    // return speedNorm * deltaIdleTime * sin(moveAngle);
    return speedNorm * deltaIdleTime * sin(-moveAngleYZ);
}

Point Bullet::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() - startPosition.getX() + dX);
    currentPositionAdjusted.setY(this->body.getCenter_y() - startPosition.getY() + dY);
    currentPositionAdjusted.setZ(this->body.getCenter_z() - startPosition.getZ() + dZ);

    return currentPositionAdjusted;
}

void Bullet::draw()
{
    glPushMatrix();

    glTranslatef(dX, -dY, dZ);
    // drawer.drawFilledSphere(this->body);
    drawer.drawSphere(this->body);

    glPopMatrix();
}

Sphere Bullet::getAdjustedBody()
{
    return Sphere(this->getCurrentPositionAdjusted(), this->body.getRadius());
}