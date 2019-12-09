#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <ratio>
#include <chrono>

#include "player.h"
#include "airportRunway.h"
#include "flightArea.h"
#include "flightEnemy.h"
#include "terrestrialEnemy.h"

#define TAKEOFF_TIME 4.0

using namespace std::chrono;
using namespace std;

class Game
{
    Draw drawer;
    FlightArea flightArea;
    Player player;
    AirportRunway airportRunway;
    vector<FlightEnemy> flightEnemies;
    vector<TerrestrialEnemy> terrestrialEnemies;
    vector<Bullet*> playerBullets;
    vector<Bullet*> enemyBullets;
    vector<Bomb*> bombs;
    GLfloat deltaIdleTime;
    bool gameOver;
    bool gameWin;
    bool nightMode;

    void updateTakeOff(high_resolution_clock::time_point currentTime, GLfloat takeOffTimeElapsed);
    vector<GLfloat> calcTakeOffAcceleration();
    Point currentTakeOffPosition(GLfloat time);
    GLfloat calcSizeIncreaseAcceleration();
    GLfloat currentRadius(GLfloat time);
    GLint amountOfDamagedTerrestrialEnemies();
    GLint amountOfUndamagedTerrestrialEnemies();
    void drawFlightArea(GLuint groundTexture, GLuint skyTexture, GLuint horizontTexture);
    void drawPlayer(GLuint playerMainBodyTexture, GLuint tailAndPropellerTexture);
    void drawAirportRunway(GLuint roadTexture);
    void drawFlightEnemies(GLuint enemyMainBodyTexture, GLuint tailAndPropellerTexture);
    void drawTerrestrialEnemies(GLuint TerrestrialEnemiesTexture);
    void drawPlayerBullets();
    void drawEnemyBullets();
    void drawBullets();
    void drawBombs();
    void drawScoreboard();
    void movePlayer();
    void moveFlightEnemies();
    void movePlayerBullets();
    void moveEnemyBullets();
    void moveBullets();
    void moveBombs();
    bool checkFlightEnemiesCollision();
    bool isPlayerInsideFlightArea(Player& player);
    bool isFlightEnemyInsideFlightArea(FlightEnemy& flightEnemy);
    void erasePlayerBullets();
    void eraseEnemyBullets();
    void eraseBullets();
    void eraseBombs();
    bool isBulletInsideFlightArea(Bullet* bullet);
    bool isBombInsideFlightArea(Bomb *bomb);
    void callGameOver();
    void callGameWin();
    void initFlightEnemiesSpeed();
    void initFlightEnemiesPosition();
    void initTerrestrialEnemiesPosition();
    GLfloat calcFinalSpeed();
    bool checkPlayerBulletCollision(FlightEnemy& FlightEnemy);
    bool checkEnemyBulletCollision();
    bool checkBombCollision(Bomb* bomb);

public:
    Game() {}

    AirportRunway &getAirportRunway()
    {
        return airportRunway;
    }

    FlightArea &getFlightArea()
    {
        return flightArea;
    }

    Player &getPlayer()
    {
        return player;
    }

    bool isGameOver() {
        return this->gameOver;
    }

    bool isGameWin() {
        return this->gameWin;
    }

    bool isNightMode() {
        return this->nightMode;
    }

    void setFlightArea(FlightArea flightArea)
    {
        this->flightArea = flightArea;
    }

    void setPlayer(Player player)
    {
        this->player = player;
    }

    void setAirportRunway(AirportRunway airportRunway)
    {
        this->airportRunway = airportRunway;
    }

    void setNightMode(bool state)
    {
        this->nightMode = state;
    }

    void addFlightEnemy(FlightEnemy flightEnemy)
    {
        flightEnemies.push_back(flightEnemy);
    }

    void addTerrestrialEnemy(TerrestrialEnemy terrestrialEnemy)
    {
        terrestrialEnemies.push_back(terrestrialEnemy);
    }

    bool isPlayerFlying()
    {
        return player.isFlying();
    }

    bool isPlayerTakingOff()
    {
        return player.isTakingOff();
    }

    void playerTakeOff()
    {
        player.setFlying(true);
    }

    void takeOff();
    void init();
    void drawGame(GLfloat deltaIdleTime, GLuint groundTexture, GLuint skyTexture, GLuint horizontTexture, GLuint roadTexture, GLuint playerMainBodyTexture, GLuint enemyMainBodyTexture, GLuint tailAndPropellerTexture);
    void reset();
    void rotatePlayerAirplaneCannonX(GLfloat moviment);
    void rotatePlayerAirplaneCannonY(GLfloat moviment);
    void shoot();
    void dropBomb();
    void calcMoviments();
    void moveCamera(GLfloat movimentX, GLfloat movimentY);
    void resetCameraAngle();
};

#endif