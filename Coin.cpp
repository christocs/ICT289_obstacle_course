#include "Coin.h"

#include <GL/freeglut.h>

Coin::Coin(float x, float y, float z, float radius)
{
    pos.x = x;
    pos.y = y;
    pos.z = z;
    rad = radius;
    reset();
}

void Coin::animate(const point3D& ballPos, float radius)
{
    //Check for collision of coin if not collected, mark if collected if collision occurs
    if (collected == false &&
        ballPos.x < (pos.x + radius) && ballPos.x > (pos.x - radius) &&
        ballPos.y < (pos.y + radius) && ballPos.y > (pos.y - radius) &&
        ballPos.z < (pos.z + radius) && ballPos.z > (pos.z - radius)
        )
        {
            collected = true;
        }
}

void Coin::display()
{
    //Draw coin if it isn't collected
    if (collected == false)
    {
        glColor3f(COLOUR_R, COLOUR_G, COLOUR_B);
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        glutSolidSphere(rad, 8, 8);
        glPopMatrix();
    }
}

point3D Coin::getBallVel(const point3D& vel, const point3D& prevPos, float rad)
{
    point3D returnVel = vel;
    return returnVel;
}

void Coin::reset()
{
    collected = false;
}
