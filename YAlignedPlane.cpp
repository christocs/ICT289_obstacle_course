#include "YAlignedPlane.h"
#include <GL/freeglut.h>

#include <algorithm>
#include <iostream>

#define X_Z_COLLISION_MARGIN 1.5

#define JUMP_GENEROSITY 20

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

point3D YAlignedPlane::getBallVel(const point3D& vel, const point3D& prevPos, float radius)
{
    point3D newVel = vel;
    //Inverts velocity and applies bounce coefficient, if collision detected
    if (collisionDetected(vel, prevPos, radius))
    {
        //newVel.y = -(bounceCoefficient * vel.y);
        newVel.y = std::abs(bounceCoefficient * vel.y);
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
        //Check if secondary axis aligns (generously)
        if ((newPos.x - (radius / X_Z_COLLISION_MARGIN)) <= std::max(axis2Min, axis2Max) &&
                (newPos.x + (radius / X_Z_COLLISION_MARGIN)) >= std::min(axis2Min, axis2Max) )
        {
            //Check if third axis aligns (generously)
            if ((newPos.z - (radius / X_Z_COLLISION_MARGIN)) <= std::max(axis3Min, axis3Max) &&
                    (newPos.z + (radius / X_Z_COLLISION_MARGIN)) >= std::min(axis3Min, axis3Max) )
            {
                detected = true;
            }
        }
    }

    return detected;
}

bool YAlignedPlane::touchingFloor(const point3D& currPos, float radius)
{
    bool detected = false;

    //Check if main axis aligns (generously)
    if (currPos.y <= mainAxis + radius + JUMP_GENEROSITY && currPos.y >= mainAxis - (radius / 2) )
    {
        //Check if secondary axis aligns (generously)
        if ((currPos.x + radius / X_Z_COLLISION_MARGIN) <= std::max(axis2Min, axis2Max) &&
                (currPos.x - radius / X_Z_COLLISION_MARGIN) >= std::min(axis2Min, axis2Max) )
        {
            //Check if third axis aligns (generously)
            if ((currPos.z + radius / X_Z_COLLISION_MARGIN) <= std::max(axis3Min, axis3Max) &&
                    (currPos.z - radius / X_Z_COLLISION_MARGIN) >= std::min(axis3Min, axis3Max) )
            {
                detected = true;
            }
        }
        detected = true;
    }

    return detected;
}
