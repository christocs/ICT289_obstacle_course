#ifndef BALL_H
#define BALL_H

#include "direction.h"
#include "point3D.h"
#include "direction.h"

//Struct for ball
struct ball
{
    //Previous position of ball's centre (from last tick)
    point3D prevPos;

    //Current position of ball's centre
    point3D currPos;

    //Previous velocity of the ball (from last tick)
    point3D prevVel;

    //Previous velocity of the ball
    point3D currVel;

    //Current acceleration of the ball in 3d space in metres per second
    point3D acc;

    //Determines whether the ball is rotating on the x, y or z axis
    point3D rotation;

    //Determines how much the ball rotates in a certain direction in degrees (for example if rotationAngle = 10, then the ball rotates
    // 10 degrees). This does not determine what direction the ball rotates (point3D rotation determines this), ONLY the amount
    // amount it rotates by and thus is direction neutral.
    float rotationAngle;

    //Radius of ball in metres
    float radius;

    //Time of the last tick
    float prevTime;

    //Time of the current tick
    float currTime;

    //Acceleration caused by making the ball move in a certain direction, usually from WASD or arrow keys
    float moveAcc;

    //Acceleration caused by specifically making the ball to jump, usually from pressing spacebar
    float jumpAcc;

    float maxMoveSpeed;

    direction moveDir;
};

#endif // BALL_H
