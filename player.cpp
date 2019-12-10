#include "player.h"

Bomb* Player::dropBomb(GLfloat deltaIdleTime)
{
    GLfloat resultingAngleXY = calc.degreesToRadians(inclinationAngle);
    GLfloat resultAngleYZ = moveAngleYZ;
    GLfloat bombSpeed = speedNorm;
    Point bombCoordinates = Point(dX, dY, dZ);
    Point bombBodyCoordinates = getCurrentPositionAdjusted();
    GLfloat bombRadius = this->body.getRadius() / 4.0;

    return new Bomb(bombBodyCoordinates, bombRadius, bombCoordinates, bombSpeed, resultingAngleXY, resultAngleYZ);
}
