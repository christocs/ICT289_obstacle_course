#include "YAlignedPlane.h"
#include <GL/freeglut.h>

void YAlignedPlane::display()
{
    glColor3f(colour.r, colour.g, colour.b);

    glBegin(GL_POLYGON);
    glVertex3d(axis2Min, mainAxis, axis3Min);
    glVertex3f(axis2Max, mainAxis, axis3Min);
    glVertex3f(axis2Max, mainAxis, axis3Max);
    glVertex3f(axis2Min, mainAxis, axis3Max);
    glEnd();
}

const point3D& YAlignedPlane::getBallVel(const point3D& vel, const point3D& prevPos, float secondsDelta)
{
    point3D newVel;
    newVel.x = vel.x;
    newVel.y = -(bounceCoefficient * vel.y);
    newVel.z = vel.z;

    return newVel;
}
