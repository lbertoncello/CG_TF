#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "sphere.h"
#include "circle.h"
#include "bullet.h"
#include "draw.h"
#include "calc.h"

#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4

#define PI 3.14159265

class Airplane
{
protected:
    Sphere body;
    Point currentPosition;
    Point startPosition;
    GLfloat initialRadius;
    GLfloat dX = 0.0; //variação em X
    GLfloat dY = 0.0; //variação em Y
    GLfloat dZ = 0.0; //variação em Z
    GLfloat inclinationAngle = 0.0;
    GLfloat speedNorm = 0.0;
    GLfloat speedIncrement = 5.0;
    bool turningLeft = false;
    bool turningRight = false;
    bool turningUp = false;
    bool turningDown = false;
    bool flying = false;
    bool takingOff = false;
    bool startPositionInitialized = false;
    bool initialRadiusInitialized = false;
    Draw drawer;
    vector<GLfloat> speed;
    GLfloat moveAngleXY;
    GLfloat moveAngleYZ;
    GLfloat airplaneSpeedMultiplier = 1.0;
    GLfloat bulletSpeedMultiplier = 1.0;
    Calc calc;
    GLfloat cannonAngleX = 0.0;
    GLfloat cannonAngleY = 0.0;
    GLfloat propellerAngle = 0.0;
    bool destroyed = false;
    GLfloat camAngleX = 0;
    GLfloat camAngleY = 0;
    GLfloat minimumZ = 0;
    GLfloat maximumZ = 0;

    void speedInit()
    {
        speed.push_back(0.0);
        speed.push_back(0.0);
        speed.push_back(0.0);
    }

    void drawMainBody(GLuint mainBodyTexture);
    void drawTail(GLuint tailTexture);
    void drawCockpit();
    void drawWings(GLuint wingsTexture, GLuint propellerTexture);
    void drawPropeller();
    void drawCannon();
    void updateTurnRightAngle(GLfloat deltaIdleTime);
    void updateTurnLeftAngle(GLfloat deltaIdleTime);
    void updateTurnUpAngle(GLfloat deltaIdleTime);
    void updateTurnDownAngle(GLfloat deltaIdleTime);
    GLfloat getNextMoveAngleXY(GLfloat deltaIdleTime);
    GLfloat getNextMoveAngleYZ(GLfloat deltaIdleTime);
    GLfloat calcNextMovement_x(GLfloat deltaIdleTime, GLfloat nextMoveAngleXY);
    GLfloat calcNextMovement_y(GLfloat deltaIdleTime, GLfloat nextMoveAngleXY);
    GLfloat calcNextMovement_z(GLfloat deltaIdleTime, GLfloat nextMoveAngleYZ);
    void updateInclinationAngle(GLfloat deltaIdleTime);
    Point getPositionAdjusted(Point position);
    void moveCameraX(GLfloat moviment, GLfloat deltaIdleTime);
    void moveCameraY(GLfloat moviment, GLfloat deltaIdleTime);

public:
    Airplane()
    {
        speedInit();
    }

    Airplane(Sphere body)
    {
        this->body = body;
        initialRadius = body.getRadius();
        initialRadiusInitialized = true;
        speedInit();
    }

    Airplane(Sphere body, GLfloat airplaneSpeedMultiplier, GLfloat bulletSpeedMultiplier)
    {
        this->body = body;
        this->airplaneSpeedMultiplier = airplaneSpeedMultiplier;
        this->bulletSpeedMultiplier = bulletSpeedMultiplier;
        initialRadius = body.getRadius();
        initialRadiusInitialized = true;
        speedInit();
    }

    Sphere &getBody()
    {
        return body;
    }

    Point getCurrentPosition()
    {
        return currentPosition;
    }

    Point getStartPosition()
    {
        return startPosition;
    }

    GLfloat getInitialRadius()
    {
        return initialRadius;
    }

    bool isFlying()
    {
        return flying;
    }

    bool isTakingOff()
    {
        return takingOff;
    }

    bool isTurningLeft()
    {
        return turningLeft;
    }

    bool isTurningRight()
    {
        return turningRight;
    }

    bool isTurningUp()
    {
        return turningUp;
    }

    bool isTurningDown()
    {
        return turningDown;
    }

    vector<GLfloat> &getSpeed()
    {
        return speed;
    }

    GLfloat getSpeedMultiplier()
    {
        return airplaneSpeedMultiplier;
    }

    GLfloat getSpeedNorm()
    {
        return speedNorm;
    }

    GLfloat getSpeedIncrement()
    {
        return speedIncrement;
    }

    GLfloat getDX(){
        return dX;
    }

    GLfloat getDY(){
        return dY;
    }

    GLfloat getDZ(){
        return dZ;
    }

    GLfloat getCamAngleX_radians() {
        return camAngleX;
    }


    GLfloat getCamAngleX_degrees() {
        return calc.radiansToDegrees(camAngleX);
    }

    void setBody(Sphere body)
    {
        this->body = body;

        if (initialRadiusInitialized == false)
        {
            initialRadius = body.getRadius();
            initialRadiusInitialized = true;
        }
    }

    void setCurrentPosition(Point currentPosition)
    {
        if (startPositionInitialized == false)
        {
            startPosition.setX(currentPosition.getX());
            startPosition.setY(currentPosition.getY());
            startPositionInitialized = true;
        }

        dX = currentPosition.getX();
        dY = currentPosition.getY();

        this->currentPosition = currentPosition;
    }

    void setFlying(bool flying)
    {
        this->flying = flying;
    }

    void setTakingOff(bool takingOff)
    {
        this->takingOff = takingOff;
    }

    void setSpeed(vector<GLfloat> speed)
    {
        speedNorm = calc.norm(speed) * this->airplaneSpeedMultiplier;
        moveAngleXY = 0;
        moveAngleYZ = 0;
    }

    void setSpeedNorm(GLfloat speedNorm)
    {
        this->speedNorm = speedNorm;
    }

    void setAirplaneSpeedMultiplier(GLfloat airplaneSpeedMultiplier)
    {
        this->airplaneSpeedMultiplier = airplaneSpeedMultiplier;
    }

    void setInclinationAngle(GLfloat inclinationAngle)
    {
        this->inclinationAngle = inclinationAngle;
    }

    GLfloat getInclinationAngle()
    {
        return this->inclinationAngle;
    }

    void setBulletSpeedMultiplier(GLfloat bulletSpeedMultiplier)
    {
        this->bulletSpeedMultiplier = bulletSpeedMultiplier;
    }

    void setTurningLeft(bool turningLeft)
    {
        this->turningLeft = turningLeft;
    }

    void setTurningRight(bool turningRight)
    {
        this->turningRight = turningRight;
    }

    void setTurningUp(bool turningUp) 
    {
        this->turningUp = turningUp;
    }

    void setTurningDown(bool turningDown)
    {
        this->turningDown = turningDown;
    }

    void setSpeedIncrement(GLfloat speedIncrement)
    {
        this->speedIncrement = speedIncrement;
    }

    void incrementPropellerAngle()
    {
        this->propellerAngle += 0.10 * speedNorm;
    }

    void setPropellerAngle(GLfloat propellerAngle)
    {
        this->propellerAngle = propellerAngle;
    }

    bool isDestroyed()
    {
        return destroyed;
    }

    void setDestroyed(bool destroyed)
    {
        this->destroyed = destroyed;
    }

    void setMinimumZ(GLfloat minimumZ) {
        this->minimumZ = minimumZ;
    }

    void setMaximumZ(GLfloat maximumZ) {
        this->maximumZ = maximumZ;
    }

    void draw(GLuint mainBodyTexture, GLuint tailAndPropellerTexture);
    void move(GLfloat deltaIdleTime);
    bool checkIntersection(Circle flightAreaBody, Sphere enemyBody, GLfloat deltaIdleTime);
    GLfloat calcMovement_x(GLfloat deltaIdleTime);
    GLfloat calcMovement_y(GLfloat deltaIdleTime);
    GLfloat calcMovement_z(GLfloat deltaIdleTime);
    Sphere getAdjustedBody();
    bool isInside(Sphere sphere, GLint moveDirection, GLfloat deltaIdleTime);
    Point getNextPosition(GLfloat deltaIdleTime);
    void updateTurningAngles(GLfloat deltaIdleTime);
    void incrementSpeed();
    void incrementSpeed(GLfloat speedIncrement);
    void decrementSpeed();
    void decrementSpeed(GLfloat speedIncrement);
    void reset();
    void teleport();
    Point getCurrentPositionAdjusted();
    void rotateCannonX(GLfloat moviment, GLfloat deltaIdleTime);
    void rotateCannonY(GLfloat moviment, GLfloat deltaIdleTime);
    Bullet *shoot(GLfloat deltaIdleTime);
    Point getLookingPoint1();
    Point getCamPoint1();
    Point getLookingPoint2();
    Point getCamPoint2();
    Point getLookingPoint3();
    Point getCamPoint3();
    void moveCamera(GLfloat movimentX, GLfloat movimentY, GLfloat deltaIdleTime);
    void resetCameraAngle();
};

#endif