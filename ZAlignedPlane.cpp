#include "ZAlignedPlane.h"
#include <freeglut.h>

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

point3D ZAlignedPlane::getBallVel(const point3D& vel, const point3D& prevPos, float radius, float secondsDelta)
{
    point3D newVel = vel;

    //Checks if the ball's tip hits the main part of the plane
    if (prevPos.z >= mainAxis - radius && prevPos.z <= mainAxis + radius)
    {
        newVel.z = -(bounceCoefficient * vel.z);
    } //else if (do edge detection here)
    //Checks if the ball hits the edge of the plane

    return newVel;
}
