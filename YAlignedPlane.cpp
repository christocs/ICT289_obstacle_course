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

point3D YAlignedPlane::getBallVel(const point3D& vel, const point3D& prevPos, float radius, float secondsDelta)
{
    point3D newVel = vel;

    //Checks if the ball's tip hits the main part of the plane
    if (prevPos.y >= mainAxis - radius && prevPos.y <= mainAxis + radius)
    {
        newVel.y = -(bounceCoefficient * vel.y);
    } //else if (do edge detection here)
    //Checks if the ball hits the edge of the plane

    return newVel;
}
