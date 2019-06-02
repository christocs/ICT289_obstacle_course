#include "ZAlignedPlane.h"
#include <GL/freeglut.h>

void ZAlignedPlane::display()
{
    glColor3f(colour.r, colour.g, colour.b);

    glBegin(GL_POLYGON);
    glVertex3d(axis2Min, axis3Min, mainAxis);
    glVertex3d(axis2Max, axis3Min, mainAxis);
    glVertex3d(axis2Max, axis3Max, mainAxis);
    glVertex3d(axis2Min, axis3Max, mainAxis);
    glEnd();
}

const point3D& ZAlignedPlane::getBallVel(const point3D& vel, const point3D& prevPos, float secondsDelta)
{
    point3D newVel;
    newVel.x = vel.x;
    newVel.y = vel.y;
    newVel.z = -(bounceCoefficient * vel.z);

    return newVel;
}
