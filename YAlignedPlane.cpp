#include "YAlignedPlane.h"
#include <GL/freeglut.h>

#include <algorithm>

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

point3D& YAlignedPlane::getBallVel(const point3D& vel, const point3D& prevPos, float radius)
{
    point3D newVel = vel;
    //Inverts velocity and applies bounce coefficient, if collision detected
    if (collisionDetected(vel, prevPos, radius))
    {
        newVel.y = -(bounceCoefficient * vel.y);
    }

    return newVel;
}

bool YAlignedPlane::collisionDetected(const point3D& vel, const point3D& prevPos, float radius)
{
    bool detected = false;
    point3D newPos = prevPos;
    newPos.x += vel.x;
    newPos.y += vel.y;
    newPos.z += vel.z;

    //Check if main axis aligns
    if (newPos.y <= mainAxis + radius && newPos.y >= mainAxis - radius)
    {
        //Check if secondary axis aligns (generous, allows ball to be half the ball's radius out)
        if ((newPos.x + radius / 2.0) <= std::max(axis2Min, axis2Max) &&
                (newPos.x - radius / 2.0) >= std::min(axis2Min, axis2Max) )
        {
            //Check if third axis aligns (generous, allows ball to be half the ball's radius out)
            if ((newPos.z + radius / 2.0) <= std::max(axis3Min, axis3Max) &&
                    (newPos.z - radius / 2.0) >= std::min(axis3Min, axis3Max) )
            {
                detected = true;
            }
        }
    }

    return detected;
}

bool YAlignedPlane::touchingFloor(const point3D& vel, const point3D& prevPos, float radius)
{
    bool detected = false;
    point3D newPos = prevPos;
    newPos.x += vel.x;
    newPos.y += vel.y;
    newPos.z += vel.z;

    //Check if main axis aligns (generous check if the ball isn't going under the plane)
    if (newPos.y <= mainAxis + radius && newPos.y >= mainAxis - (radius / 2.0) )
    {
        //Check if secondary axis aligns (generous, allows ball to be half the ball's radius out)
        if ((newPos.x + radius / 2.0) <= std::max(axis2Min, axis2Max) &&
                (newPos.x - radius / 2.0) >= std::min(axis2Min, axis2Max) )
        {
            //Check if third axis aligns (generous, allows ball to be half the ball's radius out)
            if ((newPos.z + radius / 2.0) <= std::max(axis3Min, axis3Max) &&
                    (newPos.z - radius / 2.0) >= std::min(axis3Min, axis3Max) )
            {
                detected = true;
            }
        }
    }

    return detected;
}
