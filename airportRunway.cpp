#include "airportRunway.h"

void AirportRunway::setAdjustedBody(GLfloat coordinateCorrection_x, GLfloat coordinateCorrection_y)
{
    Point p1(-coordinateCorrection_x + this->getBody().getPoint1_x(), -coordinateCorrection_y + this->getBody().getPoint1_y());
    Point p2(-coordinateCorrection_x + this->getBody().getPoint2_x(), -coordinateCorrection_y + this->getBody().getPoint2_y());

    this->adjustedBody = Line(p1, p2);
}

void AirportRunway::draw(GLuint roadTexture)
{
    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glBindTexture(GL_TEXTURE_2D, roadTexture);

    Line temp = this->adjustedBody;
    temp.getPoint1().setY(-temp.getPoint1_y());
    temp.getPoint2().setY(-temp.getPoint2_y());

    glPushMatrix();
    glTranslatef(temp.getPoint1_x(), temp.getPoint1_y(), 0.0);
    glRotatef(-this->calcInclinationAngle(), 0.0, 0.0, 1.0);
    GLfloat x2novo = temp.getPoint2_x() * cos(this->calcInclinationAngle()*(M_PI/180)) - temp.getPoint2_y() * sin(this->calcInclinationAngle()*(M_PI/180));
    Point p1(-10.0, 20.0, 0.1);
    Point p2(-10.0, -20.0, 0.1);
    Point p3(x2novo + 20, -20.0, 0.1);
    Point p4(x2novo + 20, 20.0, 0.1);

    // drawer.drawLine(temp);
    drawer.drawPlane(p1, p2, p3, p4);
    glPopMatrix();
}

GLfloat AirportRunway::calcInclinationAngle()
{
    return calc.radiansToDegrees(
        atan2f(
            body.getPoint2_y() - body.getPoint1_y(),
            body.getPoint2_x() - body.getPoint1_x()));
}
