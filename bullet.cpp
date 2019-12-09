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
    return speedNorm * deltaIdleTime * sin(moveAngleYZ);
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

    // GLfloat mat_emission[] = {0.0, 0.0, 0.0, 0.0};
    // GLfloat mat_ambient[] = {0.0, 1.0, 0.0, 1.0};
    // GLfloat mat_diffuse[] = {0.0, 1.0, 0.0, 1.0};
    // GLfloat mat_specular[] = {0.0, 1.0, 0.0, 1.0};
    // // GLfloat mat_shininess[] = {1.0, 1.0, 1.0, 1.0};

    // glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    // glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // // glMaterialfv(GL_FRONT, GL_SHININESS, mat_ambient_r);

    glTranslatef(dX, -dY, dZ);
    // drawer.drawFilledSphere(this->body);
    drawer.drawSphere(this->body);

    glPopMatrix();
}

Sphere Bullet::getAdjustedBody()
{
    return Sphere(this->getCurrentPositionAdjusted(), this->body.getRadius());
}