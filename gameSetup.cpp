#include "gameSetup.h"

void GameSetup::display(void)
{
    double camDist = 800;
    double camXYAngle = 0;
    double camXZAngle = 0;
    int toggleCam = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (toggleCam == 0)
    {
        // PrintText(0.1, 0.1, "Movable Camera", 0, 1, 0);
        glTranslatef(0, 0, -camDist);
        glRotatef(camXZAngle, 1, 0, 0);
        glRotatef(camXYAngle, 0, 1, 0);
    }
    else if (toggleCam == 1)
    {
        // PrintText(0.1, 0.1, "Static Camera at a Distance", 0, 1, 0);
        gluLookAt(10, 10, 50, 0, 0, 0, 0, 1, 0);
    }
    else if (toggleCam == 2)
    {
        // PrintText(0.1, 0.1, "Sun Camera", 0, 1, 0);
        // gluLookAt(0, 0, 0, -sin(angleYear / 180 * M_PI), 0, -cos(angleYear / 180 * M_PI), 0, 1, 0);
    }

    GLfloat light_position[] = {0.0, 0.0, 10.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
    //              no_mat);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    // glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);

    gameRuntime.getGame().drawGame(deltaIdleTime);

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
    // glViewport(0, 0, (GLsizei)500, (GLsizei)500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluPerspective(45, (GLfloat)h / (GLfloat)w, 2, 2000);
    else
        gluPerspective(45, (GLfloat)w / (GLfloat)h, 2, 2000);
    
    // gluPerspective(45, (GLfloat)w *0 / (GLfloat)h, 2, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void GameSetup::init(void)
{
    gameRuntime.getGame().init();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    //    glShadeModel (GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

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
