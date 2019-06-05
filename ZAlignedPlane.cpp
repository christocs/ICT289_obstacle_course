#include "ZAlignedPlane.h"
#include <GL/freeglut.h>

#include <algorithm>

#define X_Y_COLLISION_MARGIN 4

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

point3D ZAlignedPlane::getBallVel(const point3D& vel, const point3D& prevPos, float radius)
{
    point3D newVel = vel;
    //Inverts velocity and applies bounce coefficient, if collision detected
    if (collisionDetected(vel, prevPos, radius))
    {
        newVel.z = -(bounceCoefficient * vel.z);
    }

    return newVel;
}


bool ZAlignedPlane::collisionDetected(const point3D& vel, const point3D& prevPos, float radius)
{
    bool detected = false;
    point3D newPos = prevPos;
    newPos.x += vel.x;
    newPos.y += vel.y;
    newPos.z += vel.z;

    //Check if main axis aligns
    if (newPos.z <= mainAxis + radius && newPos.z >= mainAxis - radius)
    {
        //Check if secondary axis aligns
        if ((newPos.x - (radius / X_Y_COLLISION_MARGIN)) <= std::max(axis2Min, axis2Max) &&
            (newPos.x + (radius / X_Y_COLLISION_MARGIN)) >= std::min(axis2Min, axis2Max) )
        {
            //Check if third axis aligns
            if ((newPos.y - (radius / X_Y_COLLISION_MARGIN)) <= std::max(axis3Min, axis3Max) &&
                (newPos.y + (radius / X_Y_COLLISION_MARGIN)) >= std::min(axis3Min, axis3Max) )
            {
                detected = true;
            }
        }
    }

    return detected;
}
