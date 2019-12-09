#include "flightArea.h"

void FlightArea::draw(GLfloat heightOfSky, GLuint groundTexture, GLuint skyTexture, GLuint horizontTexture)
{
    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

    //paredes
    glBindTexture (GL_TEXTURE_2D, horizontTexture);
    drawer.drawCylinderTube(this->area.getRadius(), heightOfSky);

    //teto
    glPushMatrix();
    glTranslatef(0.0, heightOfSky, 0.0);
    glBindTexture(GL_TEXTURE_2D, skyTexture);
    drawer.drawFilledCircle(this->area);
    glPopMatrix();
    
    //chao
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    drawer.drawFilledCircle(this->area);
    glPopMatrix();
}

