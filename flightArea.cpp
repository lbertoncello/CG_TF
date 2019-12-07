#include "flightArea.h"

void FlightArea::draw(GLuint groundTexture, GLuint skyTexture)
{
    GLfloat mat_ambient_b[] = { 0.0, 0.0, 1.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_b);


    // drawer.drawFilledCircle(this->area);
    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

    glBindTexture (GL_TEXTURE_2D, skyTexture);
    drawer.drawCylinder(this->area);

    // glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    // glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    drawer.drawFilledCircle(this->area);
    glPopMatrix();
}

