#include "XAlignedPlane.h"
#include <GL/freeglut.h>

#include <algorithm>

#define Y_Z_COLLISION_MARGIN 4

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

point3D XAlignedPlane::getBallVel(const point3D& vel, const point3D& prevPos, float radius)
{
    point3D newVel = vel;
    //Inverts velocity and applies bounce coefficient, if collision detected
    if (collisionDetected(vel, prevPos, radius))
    {
        newVel.x = -(bounceCoefficient * vel.x);
    }

    return newVel;
}

bool XAlignedPlane::collisionDetected(const point3D& vel, const point3D& prevPos, float radius)
{
    bool detected = false;
    point3D newPos = prevPos;
    newPos.x += vel.x;
    newPos.y += vel.y;
    newPos.z += vel.z;

    //Check if main axis aligns
    if (newPos.x <= mainAxis + radius && newPos.x >= mainAxis - radius)
    {
        //Check if secondary axis aligns
        if ((newPos.y  - (radius / Y_Z_COLLISION_MARGIN)) <= std::max(axis2Min, axis2Max) &&
            (newPos.y + (radius / Y_Z_COLLISION_MARGIN)) >= std::min(axis2Min, axis2Max) )
        {
            //Check if third axis aligns
            if ((newPos.z - (radius / Y_Z_COLLISION_MARGIN)) <= std::max(axis3Min, axis3Max) &&
                (newPos.z - (radius / Y_Z_COLLISION_MARGIN)) >= std::min(axis3Min, axis3Max) )
            {
                detected = true;
            }
        }
    }

    return detected;
}
