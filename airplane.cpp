#include "airplane.h"

void Airplane::draw()
{
    // if (!isDestroyed())
    // {
    //     glPushMatrix();
    //     glTranslatef(dX, dY, 0.0);
    //     glRotatef(inclinationAngle, 0.0, 0.0, 1.0);

    //     drawWings();
    //     drawCannon();
    //     drawMainBody();
    //     drawCockpit();
    //     drawTail();
    //     glPopMatrix();
    // }
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                 no_mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);

    glPushMatrix();

    glTranslatef(dX, -dY, dZ);
    glRotatef(-inclinationAngle, 0.0, 0.0, 1.0);

    // drawWings();
    drawCannon();
    drawMainBody();
    // drawCockpit();
    // drawTail();

    glPopMatrix();
}

void Airplane::drawMainBody()
{
    GLfloat mat_ambient_g[] = {0.0, 1.0, 0.0, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_g);

    // glutSolidCube(this->body.getRadius());
    glPushMatrix();
    // glScalef(1, 0.25, 0.30);
    drawer.drawEllipsoid(this->body);
    glPopMatrix();
    // drawer.drawEllipse(this->body);
}

void Airplane::drawTail()
{
    glPushMatrix();

    Color color(0.0, 0.0, 0.0);

    glTranslatef(-this->body.getRadius() / 2, 0.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5.0, this->body.getRadius() / 2.0, color);

    glPopMatrix();
}

void Airplane::drawCockpit()
{
    glPushMatrix();

    GLfloat cockpitRadius = this->body.getRadius() / 2.0;
    Color cockpitColor(0.0, 0.0, 0.0);

    glTranslatef(this->body.getRadius() / 3.0, 0.0, 0.0);
    drawer.drawEllipse(cockpitRadius, cockpitColor);

    glPopMatrix();
}

void Airplane::drawWings()
{
    Color wingsColor(0.0, 0.0, 0.0);
    GLfloat mat_ambient_r[] = {1.0, 0.0, 0.0, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_r);

    glPushMatrix();
    Point p1(0.0, 0.0);
    Point p2(p1.getX() + this->body.getRadius() / 3.0, p1.getY());
    Point p3(p1.getX() - this->body.getRadius() / 6.0, this->body.getRadius());
    Point p4(p1.getX() + this->body.getRadius() / 3.0 - this->body.getRadius() / 6.0, this->body.getRadius());

    glPushMatrix();

    glTranslatef(0, this->body.getRadius() / 2.0, 0.0);
    drawPropeller();

    glPopMatrix();

    drawer.drawRectangle(p4, p2, p1, p3, wingsColor);

    glPopMatrix();

    glPushMatrix();
    Point p5(0.0, 0.0);
    Point p6(p1.getX() + this->body.getRadius() / 3.0, p1.getY());
    Point p7(p1.getX() - this->body.getRadius() / 6.0, -this->body.getRadius());
    Point p8(p1.getX() + this->body.getRadius() / 3.0 - this->body.getRadius() / 6.0, -this->body.getRadius());

    glPushMatrix();

    glTranslatef(0, -this->body.getRadius() / 2.0, 0.0);
    drawPropeller();

    glPopMatrix();

    drawer.drawRectangle(p6, p8, p7, p5, wingsColor);

    glPopMatrix();
}

void Airplane::drawPropeller()
{
    Color rodColor(0.0, 0.0, 0.0);

    glPushMatrix();

    glRotatef(-90, 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5.0, this->body.getRadius() / 2.5, rodColor);

    glPopMatrix();

    glPushMatrix();

    Color propellerColor(1.0, 1.0, 0.0);

    Point p1(-this->body.getRadius() / 4.0, -this->body.getRadius() / 6.0);
    Point p2(this->body.getRadius() / 4.0, -this->body.getRadius() / 6.0);
    Point p3(0.0, 0.0);

    Point p4(-this->body.getRadius() / 4.0, this->body.getRadius() / 6.0);
    Point p5(this->body.getRadius() / 4.0, this->body.getRadius() / 6.0);
    Point p6(0.0, 0.0);

    incrementPropellerAngle();
    glTranslatef(this->body.getRadius() / 2.0, 0, 0.0);
    glRotatef(propellerAngle, 1.0, 0.0, 0.0);

    drawer.drawTriangle(p3, p2, p1, propellerColor);
    drawer.drawTriangle(p4, p5, p6, propellerColor);

    glPopMatrix();
}


void Airplane::drawCannon()
{
    glPushMatrix();

    Color color(0.0, 0.0, 0.0);
    GLfloat mat_ambient_g[] = {0.2, 0.2, 0.2, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_g);

    glTranslatef(this->body.getRadius() * 0.9, 0.0, 0.0);
    glRotatef(-90 + calc.radiansToDegrees(cannonAngle), 0.0, 0.0, 1.0);
    // drawer.drawRectangle(this->body.getRadius() / 5.0, this->body.getRadius() / 2.0, color);
    drawer.drawCylinder(this->body.getRadius() * 0.1, this->body.getRadius() * 0.5);
    glPopMatrix();
}

GLfloat Airplane::calcMovement_x(GLfloat deltaIdleTime)
{
    // return speedNorm * deltaIdleTime * cos(moveAngleXY * (M_PI / 180)) * cos(moveAngleYZ * (M_PI / 180));
    return speedNorm * deltaIdleTime * cos(moveAngleXY) * cos(moveAngleYZ);
}

GLfloat Airplane::calcMovement_y(GLfloat deltaIdleTime)
{
    // return speedNorm * deltaIdleTime * sin(moveAngleXY * (M_PI / 180)) * cos(moveAngleYZ * (M_PI / 180));
    return speedNorm * deltaIdleTime * sin(moveAngleXY) * cos(moveAngleYZ);
}

GLfloat Airplane::calcMovement_z(GLfloat deltaIdleTime)
{
    // return speedNorm * deltaIdleTime * sin(moveAngleYZ * (M_PI / 180));
    return speedNorm * deltaIdleTime * sin(moveAngleYZ);
}

void Airplane::move(GLfloat deltaIdleTime)
{
    updateTurnLeftAngle(deltaIdleTime);
    updateTurnRightAngle(deltaIdleTime);
    updateTurnUpAngle(deltaIdleTime);
    updateTurnDownAngle(deltaIdleTime);
    updateInclinationAngle(deltaIdleTime);

    dX += calcMovement_x(deltaIdleTime);
    dY -= calcMovement_y(deltaIdleTime);
    dZ += calcMovement_z(deltaIdleTime);
}

void Airplane::updateTurningAngles(GLfloat deltaIdleTime)
{
    updateTurnLeftAngle(deltaIdleTime);
    updateTurnRightAngle(deltaIdleTime);
    updateTurnUpAngle(deltaIdleTime);
    updateTurnDownAngle(deltaIdleTime);
}

GLfloat Airplane::calcNextMovement_x(GLfloat deltaIdleTime, GLfloat nextMoveAngleXY)
{
    // GLfloat cx = this->getX() + (cos(this->getAnguloJogadorVertical() * (M_PI / 180)) * cos(((this->getAnguloJogador()) * (M_PI / 180))) * velocidade * this->velocidadeMultiplicadora * this->tempoAjustador);
    // return speedNorm * deltaIdleTime * cos(nextMoveAngleXY);
    return speedNorm * deltaIdleTime * cos(moveAngleXY) * cos(moveAngleYZ);
}

GLfloat Airplane::calcNextMovement_y(GLfloat deltaIdleTime, GLfloat nextMoveAngleXY)
{
    // return speedNorm * deltaIdleTime * sin(nextMoveAngleXY);
    // return speedNorm * deltaIdleTime * sin(moveAngleXY * (M_PI / 180)) * cos(moveAngleYZ * (M_PI / 180));
    return speedNorm * deltaIdleTime * sin(moveAngleXY) * cos(moveAngleYZ);
}

GLfloat Airplane::calcNextMovement_z(GLfloat deltaIdleTime, GLfloat nextMoveAngleYZ)
{
    // return speedNorm * deltaIdleTime * sin(nextMoveAngleYZ);
    // return speedNorm * deltaIdleTime * sin(moveAngleYZ * (M_PI / 180));
    return speedNorm * deltaIdleTime * sin(moveAngleYZ);
}

Point Airplane::getNextPosition(GLfloat deltaIdleTime)
{
    GLfloat nextMoveAngleXY = getNextMoveAngleXY(deltaIdleTime);
    GLfloat nextMoveAngleYZ = getNextMoveAngleYZ(deltaIdleTime);
    Point nextPosition;

    nextPosition.setX(dX + calcNextMovement_x(deltaIdleTime, nextMoveAngleXY));
    nextPosition.setY(dY - calcNextMovement_y(deltaIdleTime, nextMoveAngleXY));
    nextPosition.setZ(dZ + calcNextMovement_z(deltaIdleTime, nextMoveAngleYZ));

    return nextPosition;
}

bool Airplane::checkIntersection(Circle flightAreaBody, Sphere enemyBody, GLfloat deltaIdleTime)
{
    Circle adjustedBody = Circle(this->getNextPosition(deltaIdleTime), this->body.getRadius());
    adjustedBody.setCenter_x(flightAreaBody.getCenter_x() + adjustedBody.getCenter_x());
    adjustedBody.setCenter_y(flightAreaBody.getCenter_y() + adjustedBody.getCenter_y());

    return adjustedBody.checkIntersection(enemyBody, this->drawer.getNumSegments());
}

// bool Airplane::isInside(Sphere sphere, GLint moveDirection, GLfloat deltaIdleTime)
// {
//     Sphere adjustedBody = this->body;
//     adjustedBody.setCenter_x(sphere.getCenter_x() + this->dX);
//     adjustedBody.setCenter_y(sphere.getCenter_y() + this->dY);

//     switch (moveDirection)
//     {
//     case MOVE_UP:
//         adjustedBody.setCenter_y(adjustedBody.getCenter_y() - calcMovement_y(deltaIdleTime));
//         break;
//     case MOVE_DOWN:
//         adjustedBody.setCenter_y(adjustedBody.getCenter_y() + calcMovement_y(deltaIdleTime));
//         break;
//     case MOVE_LEFT:
//         adjustedBody.setCenter_x(adjustedBody.getCenter_x() - calcMovement_x(deltaIdleTime));
//         break;
//     case MOVE_RIGHT:
//         adjustedBody.setCenter_x(adjustedBody.getCenter_x() + calcMovement_x(deltaIdleTime));
//         break;
//     }

//     return sphere.isInside(adjustedBody, this->drawer.getNumSegments());
// }

Sphere Airplane::getAdjustedBody()
{
    Sphere adjustedBody = this->body;
    adjustedBody.setCenter_x(adjustedBody.getCenter_x() - startPosition.getX() + this->dX);
    adjustedBody.setCenter_y(adjustedBody.getCenter_y() - startPosition.getY() + this->dY);

    return adjustedBody;
}

GLfloat Airplane::getNextMoveAngleXY(GLfloat deltaIdleTime)
{
    GLfloat nextAngle = moveAngleXY;

    if (isTurningLeft())
    {
        nextAngle += (M_PI / 2.0 * deltaIdleTime);
    }

    if (isTurningRight())
    {
        nextAngle -= (M_PI / 2.0 * deltaIdleTime);
    }

    return nextAngle;
}

GLfloat Airplane::getNextMoveAngleYZ(GLfloat deltaIdleTime)
{
    GLfloat nextAngle = moveAngleYZ;

    if (isTurningUp())
    {
        nextAngle += (M_PI / 2.0 * deltaIdleTime);
    }

    if (isTurningDown())
    {
        nextAngle -= (M_PI / 2.0 * deltaIdleTime);
    }

    return nextAngle;
}

void Airplane::updateTurnRightAngle(GLfloat deltaIdleTime)
{
    if (isTurningRight())
    {
        moveAngleXY -= M_PI / 2.0 * deltaIdleTime;
    }
}

void Airplane::updateTurnLeftAngle(GLfloat deltaIdleTime)
{
    if (isTurningLeft())
    {
        moveAngleXY += M_PI / 2.0 * deltaIdleTime;
    }
}

void Airplane::updateTurnUpAngle(GLfloat deltaIdleTime)
{
    if (isTurningUp())
    {
        moveAngleYZ += M_PI / 2.0 * deltaIdleTime;
    }
}

void Airplane::updateTurnDownAngle(GLfloat deltaIdleTime)
{
    if (isTurningDown())
    {
        moveAngleYZ -= M_PI / 2.0 * deltaIdleTime;
    }
}

void Airplane::updateInclinationAngle(GLfloat deltaIdleTime)
{
    GLfloat nextAngle = inclinationAngle;

    if (isTurningLeft())
    {
        nextAngle -= (90 * deltaIdleTime);
    }

    if (isTurningRight())
    {
        nextAngle += (90 * deltaIdleTime);
    }

    inclinationAngle = nextAngle;
}

void Airplane::reset()
{
    body.setRadius(initialRadius);
    dX = 0.0; //variação em X
    dY = 0.0; //variação em Y
    dZ = 0.0;
    moveAngleXY = 0.0;
    moveAngleYZ = 0.0;
    inclinationAngle = 0;
    speedNorm = 0.0;
    turningLeft = false;
    turningRight = false;
    flying = false;
    takingOff = false;
    startPositionInitialized = false;
    initialRadiusInitialized = false;
    cannonAngle = 0.0;
    propellerAngle = 0.0;
    destroyed = false;
}

void Airplane::incrementSpeed()
{
    speedNorm += speedIncrement;
}

void Airplane::incrementSpeed(GLfloat speedIncrement)
{
    speedNorm += speedIncrement;
}

void Airplane::decrementSpeed()
{
    speedNorm -= speedIncrement;

    if (speedNorm < 0.0)
    {
        speedNorm = 0.0;
    }
}

void Airplane::decrementSpeed(GLfloat speedIncrement)
{
    speedNorm -= speedIncrement;

    if (speedNorm < 0.0)
    {
        speedNorm = 0.0;
    }
}

void Airplane::teleport()
{
    GLfloat x = dX;
    GLfloat y = dY;

    GLfloat alpha = atan2(y, x) * 180.0 / M_PI;
    GLfloat beta = (calc.degreesToRadians(this->inclinationAngle) - M_PI / 2.0) * 180.0 / M_PI;
    GLfloat theta = (-2.0 * (alpha - beta)) * M_PI / 180.0;

    this->dX = (x * cos(theta)) - (y * sin(theta));
    this->dY = (x * sin(theta)) + (y * cos(theta));
}

Point Airplane::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() + dX - this->startPosition.getX());
    currentPositionAdjusted.setY(this->body.getCenter_y() + dY - this->startPosition.getY());

    return currentPositionAdjusted;
}

Point Airplane::getPositionAdjusted(Point position)
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() + position.getX() - this->startPosition.getX());
    currentPositionAdjusted.setY(this->body.getCenter_y() + position.getY() - this->startPosition.getY());

    return currentPositionAdjusted;
}

void Airplane::rotateCannon(GLfloat moviment, GLfloat deltaIdleTime)
{
    GLfloat nextCannonAngle = this->cannonAngle + moviment * 0.1 * deltaIdleTime;

    if (nextCannonAngle > M_PI / 4.0)
    {
        cannonAngle = M_PI / 4.0;
    }
    else if (nextCannonAngle < -M_PI / 4.0)
    {
        cannonAngle = -M_PI / 4.0;
    }
    else
    {
        cannonAngle = nextCannonAngle;
    }
}

Bullet *Airplane::shoot(GLfloat deltaIdleTime)
{
    GLfloat resultingAngle = calc.degreesToRadians(inclinationAngle) + cannonAngle;
    GLfloat bulletSpeed = speedNorm * bulletSpeedMultiplier;
    GLfloat bulletRadius = this->body.getRadius() / 8.0;
    Point bulletCoordinates;

    bulletCoordinates.setX(
        dX + body.getRadius() * cos(calc.degreesToRadians(inclinationAngle)) + this->body.getRadius() / 2.0 * cos(resultingAngle));
    bulletCoordinates.setY(
        dY + body.getRadius() * sin(calc.degreesToRadians(inclinationAngle)) + this->body.getRadius() / 2.0 * sin(resultingAngle));

    Point bulletBodyCoordinates = getPositionAdjusted(bulletCoordinates);

    return new Bullet(bulletBodyCoordinates, bulletRadius, bulletCoordinates, bulletSpeed, resultingAngle);
}

Point Airplane::getLookingPoint()
{
    //     GLfloat raio = jogador->getRaio();
    //   GLfloat anguloHorizontal = jogador->getAnguloJogador() *M_PI/180;
    //   GLfloat anguloVertical = jogador->getAnguloJogadorVertical() *M_PI/180;

    GLfloat lookingPoint_x = dX + (2 * body.getRadius() * cos(moveAngleYZ) * cos(moveAngleXY));
    GLfloat lookingPoint_y = -dY + (2 * body.getRadius() * cos(moveAngleYZ) * sin(moveAngleXY));
    GLfloat lookingPoint_z = dZ + (2 * body.getRadius() * sin(moveAngleYZ));

    return Point(lookingPoint_x, lookingPoint_y, lookingPoint_z);

    //   GLfloat distCamera_x = body.getRadius()*cos((anguloVertical+45))*cos(anguloHorizontal)*0.8;
    //   GLfloat distCamera_y = body.getRadius()*cos((anguloVertical+45))*sin(anguloHorizontal)*0.8;
    //   GLfloat distCamera_z = body.getRadius()*sin((anguloVertical+45))*0.8;

    //   gluLookAt(jogador->getX() + distCamera_x,
    //       jogador->getY() + distCamera_y,
    //       jogador->getZ() + distCamera_z,
    //       jogador->getX() + distPontaAviao_x*2,
    //       jogador->getY() + distPontaAviao_y*2,
    //       jogador->getZ() + distPontaAviao_z*2,
    //       0, 0, 1);
}

Point Airplane::getCam1Point()
{
    // GLfloat camPoint_x = dX + (body.getRadius() * cos((moveAngleYZ + 45)) * cos(moveAngleXY) * 0.8);
    // GLfloat camPoint_y = -dY + (body.getRadius() * cos((moveAngleYZ + 45)) * sin(moveAngleXY) * 0.8);
    // GLfloat camPoint_z = dZ + (body.getRadius() * sin((moveAngleYZ + 45)) * 0.8);
    GLfloat camPoint_x = dX + (body.getRadius() * cos((moveAngleYZ + calc.degreesToRadians(45))) * cos(moveAngleXY) * 0.9);
    GLfloat camPoint_y = -dY + (body.getRadius() * cos((moveAngleYZ + calc.degreesToRadians(45))) * sin(moveAngleXY) * 0.9);
    GLfloat camPoint_z = dZ + (body.getRadius() * sin((moveAngleYZ + calc.degreesToRadians(45))) * 1.5);

    return Point(camPoint_x, camPoint_y, camPoint_z);
}
