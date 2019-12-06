#include "flightArea.h"

void FlightArea::draw()
{
    GLfloat mat_ambient_b[] = { 0.0, 0.0, 1.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_b);

    // drawer.drawFilledCircle(this->area);
    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    drawer.drawCylinder(this->area);
    glPopMatrix();
}

