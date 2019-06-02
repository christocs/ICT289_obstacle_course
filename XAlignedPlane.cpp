#include "XAlignedPlane.h"
#include <GL/freeglut.h>

void XAlignedPlane::display()
{
    glColor3f(colour.r, colour.g, colour.b);

    glBegin(GL_POLYGON);
    glVertex3d(mainAxis, axis2Min, axis3Min);
    glVertex3d(mainAxis, axis2Max, axis3Min);
    glVertex3d(mainAxis, axis2Max, axis3Max);
    glVertex3d(mainAxis, axis2Min, axis3Max);
    glEnd();
}

const point3D& XAlignedPlane::getBallVel(const point3D& vel, const point3D& prevPos, float secondsDelta)
{
    point3D newVel;
    newVel.x = -(bounceCoefficient * vel.x);
    newVel.y = vel.y;
    newVel.z = vel.z;

    return newVel;
}
