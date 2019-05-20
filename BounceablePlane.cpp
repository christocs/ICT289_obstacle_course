#include "BounceablePlane.h"
#include <cmath>

BounceablePlane::BounceablePlane(const rectangleCorners& c, float amount, const colour& cl)
{
    setCorners(c);
    absorbAmount = amount;
    colour = cl;
}

float BounceablePlane::getAbsorbAmount() const
{
    return absorbAmount;
}

void BounceablePlane::setAbsorbAmount(float amount)
{
    absorbAmount = amount;
}

const colour& BounceablePlane::getColour() const
{
    return colour;
}

void BounceablePlane::setColour(const colour& cl)
{
    colour = cl;
}

const rectangleCorners& BounceablePlane::getCorners() const
{
    return corners;
}

void BounceablePlane::setCorners(const rectangleCorners& c)
{
    corners = c;
    setNormalVector(b);
    setCentre(b);
}

const point3D& BounceablePlane::calcBallVel(const point3D& vel, const point3D& prevPos, float secondsDelta)
{
    //normal collision
    bool normCollision = false;
    //collision where ball touches the edge
    bool edgeCollision = false;
    //Initial new velocity, before a collision happens
    point3D newVel;
    newVel.x *= secondsDelta;
    newVel.y *= secondsDelta;
    newVel.z *= secondsDelta;

    /** todo: Calculate if the ball is colliding with the plane
      *
      * 1. Calc where the ball should be this tick, new vel = vel * deltaT_seconds (for each axis)
      * 2. Transform the plane to be flat and apply the same transformation to the ball's position
      *     Note: may want to calculate this transformation when setting the corners of the plane
      * 3. Assuming the plane is infinite, find the cloest point of the ball to the plane
      * 4. Check if that point is on the actual plane (the transformed plane makes it easier to only measure min and max x,y,z values)
      * 5. If the point found is on the actual plane and it is touching the ball (distance <= radius), set normCollision to true
      * 6. If above is false, but the ball is found to be touching the edge of the plane, set edgeCollision to true
      */


    /** If normal collision detected, return new velocity of ball
      * Need to find out angle of reflection and apply the transformation to the ball
      * In order to find the reflection to the already-transformed plane, need to transform the plane's normal
      *   Note: may want to calculate this when setting the corners of the plane
      * Need to apply absorbAmount to the resulting vector (simple multiplication)
      */
    if (normCollision == true)
    {

    }
    /** If edge collision detected, return new velocity of ball
      * Need to find out angle of reflection and apply the transformation to the ball
      * In order to find the reflection, need to find the angle from the ball to the closest point on the plane's edge. This will be the 'normal'
      *   Note: may want to calculate this when setting the corners of the plane
      * Need to apply absorbAmount to the resulting vector (simple multiplication)
      */
    else if (edgeCollision == true)
    {

    }
    //Return velocity, unaffected by the plane, if no collisions detected
    else
    {
        return newVel;
    }
}

void BounceablePlane::display()
{
    glColor3f(colour.r, colour.g, colour.b);

    glPushMatrix ();
    glTranslatef (centre.x, centre.y, centre.z);

    glBegin(GL_POLYGON);
    glVertex3d(corner[0].x, corner[0].y, corner[0].z);
    glVertex3d(corner[1].x, corner[1].y, corner[1].z);
    glVertex3d(corner[2].x, corner[2].y, corner[2].z);
    glVertex3d(corner[3].x, corner[3].y, corner[3].z);
    glEnd();

    glPopMatrix();
}

void BounceablePlane::setNormalVector(const rectangleCorners& c)
{
    //Calc two vectors in the plane
    point3D v1;
    v1.x = c[1].x - c[0].x;
    v1.y = c[1].y - c[0].y;
    v1.z = c[1].z - c[0].z;
    point3D v2;
    v2.x = c[3].x - c[2].x;
    v2.y = c[3].y - c[2].y;
    v2.z = c[3].z - c[2].z;

    //Find cross product of the two vectors
    normal.x = v1.y * v2.z - v1.z * v2.y;
    normal.y = v1.z * v2.x - v1.x * v2.z;
    normal.z = v1.x * v2.y - v1.y * v2.x

    //normalise vector
    double magnitude = calcMagnitude(normal);
    normal.x /= magnitude;
    normal.y /= magnitude;
    normal.z /= magnitude;
}

double BounceablePlane::calcMagnitude(const point3D& v)
{
    //uses abs() from cmath to give absolute value in double, rather than int by default
    return abs(sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

void BounceablePlane::setCentre(const rectangleCorners& c)
{
    //Calc centres by taking averages
    centre.x = (c[0].x + c[1].x + c[2].x + c[3].x) / 4.0;
    centre.y = (c[0].y + c[1].y + c[2].y + c[3].y) / 4.0;
    centre.z = (c[0].z + c[1].z + c[2].z + c[3].z) / 4.0;
}
