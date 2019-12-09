#include "gameSetup.h"

void GameSetup::display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gameRuntime.getGame().calcMoviments();

    if (gameRuntime.getToggleCam() == 0)
    {
        Point camPoint = gameRuntime.getGame().getPlayer().getCamPoint1();
        Point lookingPoint = gameRuntime.getGame().getPlayer().getLookingPoint1();
        gluLookAt(camPoint.getX(), camPoint.getY(), camPoint.getZ(), lookingPoint.getX(), lookingPoint.getY(), lookingPoint.getZ(), 0, 0, 1);
    }
    else if (gameRuntime.getToggleCam() == 1)
    {
        Point camPoint = gameRuntime.getGame().getPlayer().getCamPoint2();
        Point lookingPoint = gameRuntime.getGame().getPlayer().getLookingPoint2();
        gluLookAt(camPoint.getX(), camPoint.getY(), camPoint.getZ(), lookingPoint.getX(), lookingPoint.getY(), lookingPoint.getZ(), 0, 0, 1);
    }
    else if (gameRuntime.getToggleCam() == 2)
    {
        Point camPoint = gameRuntime.getGame().getPlayer().getCamPoint3();
        Point lookingPoint = gameRuntime.getGame().getPlayer().getLookingPoint3();
        gluLookAt(camPoint.getX(), camPoint.getY(), camPoint.getZ(), lookingPoint.getX(), lookingPoint.getY(), lookingPoint.getZ(), 0, 0, 1);
    }

    if(gameRuntime.getGame().isNightMode())
    {
        glDisable(GL_LIGHT0);
    } else {
        glEnable(GL_LIGHT0);
        GLfloat light_position[] = {0.0, 0.0, 10.0, 0.0};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    }

    gameRuntime.getGame().drawGame(deltaIdleTime, this->groundTexture, this->skyTexture, this->horizontTexture, this->roadTexture, this->playerMainBodyTexture, this->enemyMainBodyTexture, this->tailAndPropellerTexture);

    /* Não esperar */
    glutSwapBuffers();
}

void GameSetup::idle(void)
{
    gameRuntime.keyOperations();

    currentIdleTime = glutGet(GLUT_ELAPSED_TIME);
    deltaIdleTime = (currentIdleTime - lastIdleTime) / 1000;
    lastIdleTime = currentIdleTime;

    glutPostRedisplay();
}

void GameSetup::reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // if (w <= h)
    //     gluPerspective(90, (GLfloat)h / (GLfloat)w, 10, 2000);
    // else
    //     gluPerspective(90, (GLfloat)w / (GLfloat)h, 10, 2000);
    // gluPerspective(90, (arena->getRaio() * 2) / (arena->getRaio() * 2), arena->getJogador()->getRaio()*0.3, arena->getRaio() * 2);
    // gluPerspective(90,
    //                (gameRuntime.getGame().getFlightArea().getArea().getRadius() * 2) / (gameRuntime.getGame().getFlightArea().getArea().getRadius() * 2),
    //                gameRuntime.getGame().getPlayer().getBody().getRadius() * 0.4,
    //                gameRuntime.getGame().getFlightArea().getArea().getRadius() * 2);
    // gluPerspective(120,
    //                (gameRuntime.getGame().getFlightArea().getArea().getRadius() * 2) / (gameRuntime.getGame().getFlightArea().getArea().getRadius() * 2),
    //                gameRuntime.getGame().getPlayer().getBody().getRadius() * 0.4,
    //                gameRuntime.getGame().getFlightArea().getArea().getRadius() * 2);

    gluPerspective(120,
                   (GLfloat)w / (GLfloat)h,
                   gameRuntime.getGame().getPlayer().getBody().getRadius() * 0.1,
                   gameRuntime.getGame().getFlightArea().getArea().getRadius() * 3);

    glMatrixMode(GL_MODELVIEW);
}

void GameSetup::init(void)
{
    gameRuntime.getGame().init();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    //    glShadeModel (GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    // glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    this->groundTexture = LoadTextureRAW("./textures/ground.bmp");
    this->skyTexture = LoadTextureRAW("./textures/sky.bmp");
    this->horizontTexture = LoadTextureRAW("./textures/horizont.bmp");
    this->roadTexture = LoadTextureRAW("./textures/road.bmp");
    this->playerMainBodyTexture = LoadTextureRAW("./textures/playerMainBody.bmp");
    this->enemyMainBodyTexture = LoadTextureRAW("./textures/enemyMainBody.bmp");
    this->tailAndPropellerTexture = LoadTextureRAW("./textures/tailAndPropeller.bmp");

    // glOrtho(-gameRuntime.getGame().getFlightArea().getArea().getRadius(),
    //         gameRuntime.getGame().getFlightArea().getArea().getRadius(),
    //         gameRuntime.getGame().getFlightArea().getArea().getRadius(),
    //         -gameRuntime.getGame().getFlightArea().getArea().getRadius(),
    //         -1, 1);

    currentIdleTime = glutGet(GLUT_ELAPSED_TIME);
    lastIdleTime = glutGet(GLUT_ELAPSED_TIME);
}

bool GameSetup::initRuntimeParameters(string filename, string arenaFilename)
{
    this->parametersReading.setGameRuntime(&this->gameRuntime);
    this->parametersReading.setArenaFilename(arenaFilename);

    return parametersReading.parametersInit(filename.c_str());
}

bool GameSetup::initArenaFile()
{
    return this->parametersReading.readArenaFile();
}

GLuint GameSetup::LoadTextureRAW(const char *filename)
{

    GLuint texture;

    Image *image = loadBMP(filename);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,               //Always GL_TEXTURE_2D
                 0,                           //0 for now
                 GL_RGB,                      //Format OpenGL uses for image
                 image->width, image->height, //Width and height
                 0,                           //The border of the image
                 GL_RGB,                      //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE,            //GL_UNSIGNED_BYTE, because pixels are stored
                                              //as unsigned numbers
                 image->pixels);              //The actual pixel data
    delete image;

    return texture;
}