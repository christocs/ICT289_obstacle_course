#include "YMovingPlatform.h"
#include <iostream>
#include <GL/freeglut.h>

YMovingPlatform::YMovingPlatform(float xMin, float xMax, float y, float zMin, float zMax, float depth, float topBounce, float wallBounce, float dist, float s, bool upStart)
{
    yMinBegin = y - depth;
    yMaxBegin = y;

    distance = dist;
    speed = s;

    up = upStart;
    beginUp = upStart;

    colour c;
    c.r = COLOUR_R;
    c.g = COLOUR_G;
    c.b = COLOUR_B;

    //Set top plane
    yPlane.setMainAxisValue(yMaxBegin);
    yPlane.setAxis2MinVal(xMin);
    yPlane.setAxis2MaxVal(xMax);
    yPlane.setAxis3MinVal(zMin);
    yPlane.setAxis3MaxVal(zMax);
    yPlane.setBounceCoefficient(topBounce);
    yPlane.setColour(c);

    //Set left-side x-aligned wall
    xPlane1.setMainAxisValue(xMax);
    xPlane1.setAxis2MinVal(yMinBegin);
    xPlane1.setAxis2MaxVal(yMaxBegin);
    xPlane1.setAxis3MinVal(zMin);
    xPlane1.setAxis3MaxVal(zMax);
    xPlane1.setBounceCoefficient(wallBounce);
    xPlane1.setColour(c);

    //Set right-side x-aligned wall
    xPlane2.setMainAxisValue(xMin);
    xPlane2.setAxis2MinVal(yMinBegin);
    xPlane2.setAxis2MaxVal(yMaxBegin);
    xPlane2.setAxis3MinVal(zMin);
    xPlane2.setAxis3MaxVal(zMax);
    xPlane2.setBounceCoefficient(wallBounce);
    xPlane2.setColour(c);

    //Set front-side z-aligned wall (closest to camera)
    zPlane1.setMainAxisValue(zMin);
    zPlane1.setAxis2MinVal(xMin);
    zPlane1.setAxis2MaxVal(xMax);
    zPlane1.setAxis3MinVal(yMinBegin);
    zPlane1.setAxis3MaxVal(yMaxBegin);
    zPlane1.setBounceCoefficient(wallBounce);
    zPlane1.setColour(c);

    //Set back-side z-aligned wall (furthest from camera)
    zPlane2.setMainAxisValue(zMax);
    zPlane2.setAxis2MinVal(xMin);
    zPlane2.setAxis2MaxVal(xMax);
    zPlane2.setAxis3MinVal(yMinBegin);
    zPlane2.setAxis3MaxVal(yMaxBegin);
    zPlane2.setBounceCoefficient(wallBounce);
    zPlane2.setColour(c);
}

void YMovingPlatform::reset()
{
    //Set top plane
    yPlane.setMainAxisValue(yMaxBegin);

    //Set left-side x-aligned wall
    xPlane1.setAxis2MinVal(yMinBegin);
    xPlane1.setAxis2MaxVal(yMaxBegin);

    //Set right-side x-aligned wall
    xPlane2.setAxis2MinVal(yMinBegin);
    xPlane2.setAxis2MaxVal(yMaxBegin);

    //Set front-side z-aligned wall (closest to camera)
    zPlane1.setAxis3MinVal(yMinBegin);
    zPlane1.setAxis3MaxVal(yMaxBegin);

    //Set back-side z-aligned wall (furthest from camera)
    zPlane2.setAxis3MinVal(yMinBegin);
    zPlane2.setAxis3MaxVal(yMaxBegin);

    up = beginUp;
}

void YMovingPlatform::animate(const point3D& currPos, float radius, float t)
{
    /* Check if directions should be changed */
    if ((xPlane1.getAxis2MinValue() < (yMinBegin - distance)))
    {
        up = true;
    }
    else if ((xPlane1.getAxis2MaxValue() > (yMaxBegin + distance)))
    {
        up = false;
    }

    //Amount of velocity to add
    float addVel = speed * t;

    /* Check which way to move the platform and apply the transformation */
    if (up)
    {
        //Set top plane
        yPlane.setMainAxisValue( yPlane.getMainAxisValue() + addVel );

        //Set left-side x-aligned wall
        xPlane1.setAxis2MinVal( xPlane1.getAxis2MinValue() + addVel );
        xPlane1.setAxis2MaxVal( xPlane1.getAxis2MaxValue() + addVel );

        //Set right-side x-aligned wall
        xPlane2.setAxis2MinVal( xPlane2.getAxis2MinValue() + addVel );
        xPlane2.setAxis2MaxVal( xPlane2.getAxis2MaxValue() + addVel );

        //Set front-side z-aligned wall (closest to camera)
        zPlane1.setAxis3MinVal( zPlane1.getAxis3MinValue() + addVel );
        zPlane1.setAxis3MaxVal( zPlane1.getAxis3MaxValue() + addVel );

        //Set back-side z-aligned wall (furthest from camera)
        zPlane2.setAxis3MinVal( zPlane2.getAxis3MinValue() + addVel );
        zPlane2.setAxis3MaxVal( zPlane2.getAxis3MaxValue() + addVel );
    }
    else
    {
        //Set top plane
        yPlane.setMainAxisValue( yPlane.getMainAxisValue() - addVel );

        //Set left-side x-aligned wall
        xPlane1.setAxis2MinVal( xPlane1.getAxis2MinValue() - addVel );
        xPlane1.setAxis2MaxVal( xPlane1.getAxis2MaxValue() - addVel );

        //Set right-side x-aligned wall
        xPlane2.setAxis2MinVal( xPlane2.getAxis2MinValue() - addVel );
        xPlane2.setAxis2MaxVal( xPlane2.getAxis2MaxValue() - addVel );

        //Set front-side z-aligned wall (closest to camera)
        zPlane1.setAxis3MinVal( zPlane1.getAxis3MinValue() - addVel );
        zPlane1.setAxis3MaxVal( zPlane1.getAxis3MaxValue() - addVel );

        //Set back-side z-aligned wall (furthest from camera)
        zPlane2.setAxis3MinVal( zPlane2.getAxis3MinValue() - addVel );
        zPlane2.setAxis3MaxVal( zPlane2.getAxis3MaxValue() - addVel );
    }
}

void YMovingPlatform::display()
{
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

point3D YMovingPlatform::getBallVel(const point3D& vel, const point3D& prevPos, float radius)
{
    int collisions = 0;
    //Average velocity from collisions
    point3D colVel;
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

bool YMovingPlatform::collisionDetected(const point3D& vel, const point3D& prevPos, float radius)
{
    bool collisions = false;

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

    return collisions;
}

bool YMovingPlatform::touchingFloor(const point3D& currPos, float radius)
{
    return yPlane.touchingFloor(currPos, radius);
}
