#include "gameRuntime.h"

bool *GameRuntime::keyStates = new bool[256];

void GameRuntime::keyOperations(void)
{
    if (!game.isGameOver() && !game.isGameWin())
    {
        if (keyStates['a'])
        {
            if (game.isPlayerFlying())
            {
                game.getPlayer().setTurningLeft(true);
            }
        }
        else
        {
            game.getPlayer().setTurningLeft(false);
        }

        if (keyStates['d'])
        {
            if (game.isPlayerFlying())
            {
                game.getPlayer().setTurningRight(true);
            }
        }
        else
        {
            game.getPlayer().setTurningRight(false);
        }
        if (keyStates['w'])
        {
            if (game.isPlayerFlying())
            {
                game.getPlayer().setTurningUp(true);
            }
        }
        else
        {
            if (!game.isPlayerTakingOff())
            {
                game.getPlayer().setTurningUp(false);
            }
        }
        if (keyStates['s'])
        {
            if (game.isPlayerFlying())
            {
                game.getPlayer().setTurningDown(true);
            }
        }
        else
        {
            if (!game.isPlayerTakingOff())
            {
                game.getPlayer().setTurningDown(false);
            }
        }
        if (keyStates['u'])
        {
            if (game.isPlayerFlying() == false && game.isPlayerTakingOff() == false)
            {
                game.takeOff();
            }
        }
        if (keyStates['n'])
        {
            game.setNightMode(!game.isNightMode());
        }
        if (keyStates['+'])
        {
            if (game.isPlayerFlying())
            {
                game.getPlayer().incrementSpeed();
            }
        }
        if (keyStates['-'])
        {
            if (game.isPlayerFlying())
            {
                game.getPlayer().decrementSpeed();
            }
        }
    }

    if (keyStates['r'])
    {
        game.reset();
    }

    if (keyStates['1'])
    {
        game.resetCameraAngle();
        this->toggleCam = 0;
    }

    if (keyStates['2'])
    {
        game.resetCameraAngle();
        this->toggleCam = 1;
    }

    if (keyStates['3'])
    {
        this->toggleCam = 2;
    }
}

void GameRuntime::keyPress(unsigned char key, GLint x, GLint y)
{
    if (key == 'a')
    {
        keyStates[key] = true;
    }
    if (key == 'd')
    {
        keyStates[key] = true;
    }
    if (key == 'w')
    {
        keyStates[key] = true;
    }
    if (key == 's')
    {
        keyStates[key] = true;
    }
    if (key == 'u')
    {
        keyStates[key] = true;
    }
    if(key == 'n')
    {
        keyStates[key] = true;
    }
    if (key == 'r')
    {
        keyStates[key] = true;
    }
    if (key == '+')
    {
        keyStates[key] = true;
    }
    if (key == '-')
    {
        keyStates[key] = true;
    }
    if (key == '1')
    {
        keyStates[key] = true;
    }
    if (key == '2')
    {
        keyStates[key] = true;
    }
    if (key == '3')
    {
        keyStates[key] = true;
    }
    if (key == ' ')
    {
        keyStates[key] = true;
    }
}

void GameRuntime::keyUp(unsigned char key, GLint x, GLint y)
{
    keyStates[key] = false; // Set the state of the current key to not pressed
}

void GameRuntime::mouse(GLint button, GLint state, GLint x, GLint y)
{
    if (!game.isGameOver() && !game.isGameWin())
    {
        if (game.isPlayerFlying())
        {
            if (button == GLUT_LEFT_BUTTON)
            {
                if (state == GLUT_UP)
                {
                    game.shoot();
                }
            }

            if (button == GLUT_RIGHT_BUTTON && keyStates[' '] == false)
            {
                rightMouseButtonPressed = true;

                if (state == GLUT_UP)
                {
                    game.dropBomb();
                    rightMouseButtonPressed = false;
                }
            }
        }
    }

    if (button == GLUT_RIGHT_BUTTON)
    {
        if (keyStates[' '] == true)
        {
            rightMouseButtonPressed = true;

            if (state == GLUT_UP)
            {
                rightMouseButtonPressed = false;
            }
        }
        else
        {
            rightMouseButtonPressed = false;
        }
    }
}

void GameRuntime::motion(GLint x, GLint y)
{
    if (!game.isGameOver() && !game.isGameWin())
    {
        if (game.isPlayerFlying())
        {
            game.rotatePlayerAirplaneCannonX(x - previousX);
            previousX = x;

            game.rotatePlayerAirplaneCannonY(y - previousY);
            previousY = y;
        }
    }
}

void GameRuntime::passiveMotion(GLint x, GLint y)
{
    previousMousePosition = mousePosition;
    mousePosition = Point(x, y);

    if (!game.isGameOver() && !game.isGameWin())
    {
        if (game.isPlayerFlying())
        {
            game.rotatePlayerAirplaneCannonX(x - previousX);
            previousX = x;

            game.rotatePlayerAirplaneCannonY(y - previousY);
            previousY = y;
        }
    }

    if (isLeftMouseButtonPressed())
    {
    }

    if (isRightMouseButtonPressed())
    {
        movingCamera = true;
        camMovimentX = mousePosition.getX() - previousMousePosition.getX();
        camMovimentY = mousePosition.getY() - previousMousePosition.getY();

        game.moveCamera(camMovimentX, camMovimentY);
    }
    else
    {
        movingCamera = false;
    }
}
