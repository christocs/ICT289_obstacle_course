#include "XAlignedPlane.h"
#include <freeglut.h>

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

point3D XAlignedPlane::getBallVel(const point3D& vel, const point3D& prevPos, float radius, float secondsDelta)
{
    point3D newVel = vel;

    //Checks if the ball's tip hits the main part of the plane
    if (prevPos.x >= mainAxis - radius && prevPos.x <= mainAxis + radius)
    {
        newVel.x = -(bounceCoefficient * vel.x);
    } //else if (do edge detection here)
    //Checks if the ball hits the edge of the plane

    return newVel;
}
