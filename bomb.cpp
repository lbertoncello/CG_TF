#include "bomb.h"

// void Bomb::calcSizeDecreaseAcceleration()
// {
//     GLfloat initialSize = this->body.getRadius();
//     GLfloat finalSize = this->body.getRadius() / 2;

//     sizeDecreaseAcceleration = calc.calcAccelerationRequired(initialSize, finalSize, 0, BOMB_LIFETIME);
// }

// GLfloat Bomb::calcCurrentRadiusVariation()
// {
//     GLfloat initialPosition = initialRadius;
//     GLfloat acceleration = sizeDecreaseAcceleration;
//     GLfloat initialSpeed = 0;

//     currentTime = std::chrono::high_resolution_clock::now();
//     duration<GLfloat> timeSpan = duration_cast<duration<GLfloat>>(currentTime - dropStartTime);
//     GLfloat sizeDecreaseTimeElapsed = timeSpan.count();

//     if (sizeDecreaseTimeElapsed >= BOMB_LIFETIME)
//     {
//         onTheGround = true;
//     }

//     return calc.calcCurrentPositionVariation(initialPosition, acceleration, initialSpeed, sizeDecreaseTimeElapsed);
// }

// void Bomb::updateSize()
// {
//     GLfloat newRadius = initialRadius + calcCurrentRadiusVariation();
//     this->body.setRadius(newRadius);
// }

void Bomb::move(GLfloat deltaIdleTime)
{
    dX += calcMovement_x(deltaIdleTime);
    dY += calcMovement_y(deltaIdleTime);
    dZ += calcMovement_z(deltaIdleTime);
}

GLfloat Bomb::calcMovement_x(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * cos(moveAngleXY) * cos(moveAngleYZ);
}

GLfloat Bomb::calcMovement_y(GLfloat deltaIdleTime)
{
    return  speedNorm * deltaIdleTime * sin(moveAngleXY) * cos(moveAngleYZ);
}

GLfloat Bomb::calcMovement_z(GLfloat deltaIdleTime)
{
    return deltaIdleTime * sin(moveAngleYZ) * -10000;
}

Point Bomb::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() - startPosition.getX() + dX);
    currentPositionAdjusted.setY(this->body.getCenter_y() - startPosition.getY() + dY);
    currentPositionAdjusted.setZ(this->body.getCenter_z() - startPosition.getZ() + dZ);

    return currentPositionAdjusted;
}

Sphere Bomb::getAdjustedBody()
{
    return Sphere(this->getCurrentPositionAdjusted(), this->body.getRadius());
}

void Bomb::draw()
{
    glPushMatrix();

    GLfloat mat_ambient_color[] = {0.33, 0.12, 0.42, 1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_color);

    glTranslatef(dX, -dY, dZ);
    // drawer.drawFilledSphere(this->body);
    glutSolidSphere(body.getRadius(), 100, 100);

    glPopMatrix();
}
