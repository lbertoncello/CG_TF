#include "flightArea.h"

void FlightArea::draw(GLfloat heightOfSky, GLuint groundTexture, GLuint skyTexture, GLuint horizontTexture)
{
    GLfloat mat_ambient_b[] = { 0.0, 0.0, 1.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_b);

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

