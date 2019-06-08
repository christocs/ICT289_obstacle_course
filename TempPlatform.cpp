#include "TempPlatform.h"
#include <GL/freeglut.h>

TempPlatform::TempPlatform(float xMin, float xMax, float y, float zMin, float zMax, float depth, float topBounce, float wallBounce, float ttl)
{
    timeToLive = ttl;
    initialTimeToLive = ttl;

    floorTouched = false;

    c1.r = COLOUR1_R;
    c1.g = COLOUR1_G;
    c1.b = COLOUR1_B;

    c2.r = COLOUR2_R;
    c2.g = COLOUR2_G;
    c2.b = COLOUR2_B;

    c3.r = COLOUR3_R;
    c3.g = COLOUR3_G;
    c3.b = COLOUR3_B;

    //Set top plane
    yPlane.setMainAxisValue(y);
    yPlane.setAxis2MinVal(xMin);
    yPlane.setAxis2MaxVal(xMax);
    yPlane.setAxis3MinVal(zMin);
    yPlane.setAxis3MaxVal(zMax);
    yPlane.setBounceCoefficient(topBounce);
    yPlane.setColour(c3);

    //Set left-side x-aligned wall
    xPlane1.setMainAxisValue(xMax);
    xPlane1.setAxis2MinVal(y - depth);
    xPlane1.setAxis2MaxVal(y);
    xPlane1.setAxis3MinVal(zMin);
    xPlane1.setAxis3MaxVal(zMax);
    xPlane1.setBounceCoefficient(wallBounce);
    xPlane1.setColour(c2);

    //Set right-side x-aligned wall
    xPlane2.setMainAxisValue(xMin);
    xPlane2.setAxis2MinVal(y - depth);
    xPlane2.setAxis2MaxVal(y);
    xPlane2.setAxis3MinVal(zMin);
    xPlane2.setAxis3MaxVal(zMax);
    xPlane2.setBounceCoefficient(wallBounce);
    xPlane2.setColour(c2);

    //Set front-side z-aligned wall (closest to camera)
    zPlane1.setMainAxisValue(zMin);
    zPlane1.setAxis2MinVal(xMin);
    zPlane1.setAxis2MaxVal(xMax);
    zPlane1.setAxis3MinVal(y - depth);
    zPlane1.setAxis3MaxVal(y);
    zPlane1.setBounceCoefficient(wallBounce);
    zPlane1.setColour(c2);

    //Set back-side z-aligned wall (furthest from camera)
    zPlane2.setMainAxisValue(zMax);
    zPlane2.setAxis2MinVal(xMin);
    zPlane2.setAxis2MaxVal(xMax);
    zPlane2.setAxis3MinVal(y - depth);
    zPlane2.setAxis3MaxVal(y);
    zPlane2.setBounceCoefficient(wallBounce);
    zPlane2.setColour(c2);
}

void TempPlatform::reset()
{
    timeToLive = initialTimeToLive;
    colour3 = true;
    floorTouched = false;
    timeSinceLastColour = 0;
}

void TempPlatform::animate(const point3D& currPos, float radius, float t)
{
    if (timeToLive > 0)
    {
        if ((floorTouched == false))
        {
            floorTouched = yPlane.touchingFloor(currPos, radius);
        }

        if (floorTouched)
        {
            timeSinceLastColour += t;
            if (timeSinceLastColour > COLOUR_CHANGE_RATE)
            {
                colour3 = !colour3;
                timeSinceLastColour = 0;
            }
            //Adjust time to live
            timeToLive -= t;
        }
    }
}

void TempPlatform::display()
{
    //Check if platform should exist before drawing
    if (timeToLive > 0)
    {
        //std::cout << "ttl > 0" << std::endl;
        //Set appropriate colour
        if (colour3)
        {
            yPlane.setColour(c3);
        }
        else
        {
            yPlane.setColour(c1);
        }

        xPlane1.display();
        xPlane2.display();
        yPlane.display();
        zPlane1.display();
        zPlane2.display();

        //Draw button of platform
        glBegin(GL_POLYGON);
        glVertex3f(yPlane.getAxis2MinValue(), xPlane1.getAxis2MinValue(), yPlane.getAxis3MinValue());
        glVertex3f(yPlane.getAxis2MinValue(), xPlane1.getAxis2MinValue(), yPlane.getAxis3MaxValue());
        glVertex3f(yPlane.getAxis2MaxValue(), xPlane1.getAxis2MinValue(), yPlane.getAxis3MaxValue());
        glVertex3f(yPlane.getAxis2MaxValue(), xPlane1.getAxis2MinValue(), yPlane.getAxis3MinValue());
        glEnd();
    }
}

point3D TempPlatform::getBallVel(const point3D& vel, const point3D& prevPos, float radius)
{
    //Average velocity from collisions
    point3D colVel;

    //make sure plat exists before calculating
    if (!(timeToLive > 0))
    {
        colVel = vel;
        return colVel;
    }
    else
    {
        int collisions = 0;

        colVel.x = 0;
        colVel.y = 0;
        colVel.z = 0;

        //Temporary velocity store for processing
        point3D tempVel;

        if (xPlane1.collisionDetected(vel, prevPos, radius))
        {
            tempVel = xPlane1.getBallVel(vel, prevPos, radius);
            colVel.x += tempVel.x;
            colVel.y += tempVel.y;
            colVel.z += tempVel.z;

            collisions++;
        }

        if (xPlane2.collisionDetected(vel, prevPos, radius))
        {
            tempVel = xPlane2.getBallVel(vel, prevPos, radius);
            colVel.x += tempVel.x;
            colVel.y += tempVel.y;
            colVel.z += tempVel.z;

            collisions++;
        }

        if (yPlane.collisionDetected(vel, prevPos, radius))
        {
            tempVel = yPlane.getBallVel(vel, prevPos, radius);
            colVel.x += tempVel.x;
            colVel.y += tempVel.y;
            colVel.z += tempVel.z;

            collisions++;
        }

        if (zPlane1.collisionDetected(vel, prevPos, radius))
        {
            tempVel = zPlane1.getBallVel(vel, prevPos, radius);
            colVel.x += tempVel.x;
            colVel.y += tempVel.y;
            colVel.z += tempVel.z;

            collisions++;
        }

        if (zPlane2.collisionDetected(vel, prevPos, radius))
        {
            tempVel = zPlane2.getBallVel(vel, prevPos, radius);
            colVel.x += tempVel.x;
            colVel.y += tempVel.y;
            colVel.z += tempVel.z;

            collisions++;
        }

        //Return average collision velocity if collisions happened
        if (collisions > 0)
        {
            //Determine average
            colVel.x /= (float) collisions;
            colVel.y /= (float) collisions;
            colVel.z /= (float) collisions;

            return colVel;
        }
        else
            //Return input velocity if no collisions occured
        {
            colVel = vel;
            return colVel;
        }
    }
}

bool TempPlatform::collisionDetected(const point3D& vel, const point3D& prevPos, float radius)
{
    bool collisions = false;

    //Check platform exists before doing collision detection
    if (timeToLive > 0)
    {
        if (xPlane1.collisionDetected(vel, prevPos, radius))
        {
            collisions = true;
        }
        else if (xPlane2.collisionDetected(vel, prevPos, radius))
        {
            collisions = true;
        }
        else if (yPlane.collisionDetected(vel, prevPos, radius))
        {
            collisions = true;
        }
        else if (zPlane1.collisionDetected(vel, prevPos, radius))
        {
            collisions = true;
        }
        else if (zPlane2.collisionDetected(vel, prevPos, radius))
        {
            collisions = true;
        }
    }

    return collisions;
}

bool TempPlatform::touchingFloor(const point3D& currPos, float radius)
{
    //Always return false if platform doesn't exist
    if (!(timeToLive > 0))
    {
        return false;
    }
    else
    {
        return yPlane.touchingFloor(currPos, radius);
    }
}
