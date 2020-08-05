#include "XMovingPlatform.h"
#include <GL/freeglut.h>

XMovingPlatform::XMovingPlatform(float xMin, float xMax, float y, float zMin, float zMax, float depth, float topBounce, float wallBounce, float dist, float s, bool leftStart)
{
    xMinBegin = xMin;
    xMaxBegin = xMax;

    distance = dist;
    speed = s;

    left = leftStart;
    beginLeft = leftStart;

    colour c1;
    c1.r = COLOUR1_R;
    c1.g = COLOUR1_G;
    c1.b = COLOUR1_B;
    colour c2;
    c2.r = COLOUR2_R;
    c2.g = COLOUR2_G;
    c2.b = COLOUR2_B;

    //Set top plane
    yPlane.setMainAxisValue(y);
    yPlane.setAxis2MinVal(xMin);
    yPlane.setAxis2MaxVal(xMax);
    yPlane.setAxis3MinVal(zMin);
    yPlane.setAxis3MaxVal(zMax);
    yPlane.setBounceCoefficient(topBounce);
    yPlane.setColour(c1);

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

void XMovingPlatform::reset()
{
    //Set top plane
    yPlane.setAxis2MinVal(xMinBegin);
    yPlane.setAxis2MaxVal(xMaxBegin);

    //Set left-side x-aligned wall
    xPlane1.setMainAxisValue(xMaxBegin);

    //Set right-side x-aligned wall
    xPlane2.setMainAxisValue(xMinBegin);

    //Set front-side z-aligned wall (closest to camera)
    zPlane1.setAxis2MinVal(xMinBegin);
    zPlane1.setAxis2MaxVal(xMaxBegin);

    //Set back-side z-aligned wall (furthest from camera)
    zPlane2.setAxis2MinVal(xMinBegin);
    zPlane2.setAxis2MaxVal(xMaxBegin);

    left = beginLeft;
}

void XMovingPlatform::animate(const point3D& currPos, float radius, float t)
{
    /* Check if directions should be changed */
    if ((yPlane.getAxis2MinValue() < (xMinBegin - distance)))
    {
        left = false;
    }
    else if ((yPlane.getAxis2MaxValue() > (xMaxBegin + distance)))
    {
        left = true;
    }

    //Amount of velocity to add
    float addVel = speed * t;

    /* Check which way to move the platform and apply the transformation */
    if (left)
    {
        //Set top plane
        yPlane.setAxis2MinVal( yPlane.getAxis2MinValue() - addVel );
        yPlane.setAxis2MaxVal( yPlane.getAxis2MaxValue() - addVel );

        //Set left-side x-aligned wall
        xPlane1.setMainAxisValue( xPlane1.getMainAxisValue() - addVel );

        //Set right-side x-aligned wall
        xPlane2.setMainAxisValue( xPlane2.getMainAxisValue() - addVel );

        //Set front-side z-aligned wall (closest to camera)
        zPlane1.setAxis2MinVal( zPlane1.getAxis2MinValue() - addVel );
        zPlane1.setAxis2MaxVal( zPlane1.getAxis2MaxValue() - addVel );

        //Set back-side z-aligned wall (furthest from camera)
        zPlane2.setAxis2MinVal( zPlane2.getAxis2MinValue() - addVel );
        zPlane2.setAxis2MaxVal( zPlane2.getAxis2MaxValue() - addVel );
    }
    else
    {
        //Set top plane
        yPlane.setAxis2MinVal( yPlane.getAxis2MinValue() + addVel );
        yPlane.setAxis2MaxVal( yPlane.getAxis2MaxValue() + addVel );

        //Set left-side x-aligned wall
        xPlane1.setMainAxisValue( xPlane1.getMainAxisValue() + addVel );

        //Set right-side x-aligned wall
        xPlane2.setMainAxisValue( xPlane2.getMainAxisValue() + addVel );

        //Set front-side z-aligned wall (closest to camera)
        zPlane1.setAxis2MinVal( zPlane1.getAxis2MinValue() + addVel );
        zPlane1.setAxis2MaxVal( zPlane1.getAxis2MaxValue() + addVel );

        //Set back-side z-aligned wall (furthest from camera)
        zPlane2.setAxis2MinVal( zPlane2.getAxis2MinValue() + addVel );
        zPlane2.setAxis2MaxVal( zPlane2.getAxis2MaxValue() + addVel );
    }
}

void XMovingPlatform::display()
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

point3D XMovingPlatform::getBallVel(const point3D& vel, const point3D& prevPos, float radius)
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

bool XMovingPlatform::collisionDetected(const point3D& vel, const point3D& prevPos, float radius)
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

bool XMovingPlatform::touchingFloor(const point3D& currPos, float radius)
{
    return yPlane.touchingFloor(currPos, radius);
}
