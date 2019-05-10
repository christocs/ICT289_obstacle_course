#ifndef MAINHEADER_H_INCLUDED
#define MAINHEADER_H_INCLUDED

#include "Module.h"
#include "structs.h"

// The time in milliseconds between timer ticks
#define TIMERMSECS 11

//Struct for ball
struct
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

    //mass of ball in kg
    float mass;

    //Time of the last tick
    float prevTime;

    //Time of the current tick
    float currTime;

    //Acceleration caused by making the ball move in a certain direction, usually from WASD or arrow keys
    float moveAcc;

    float maxMoveSpeed;

    //Acceleration caused by specifically making the ball to jump, usually from pressing spacebar
    float jumpAcc;

    //Pointer to the module the ball is currently in
    Module *currentModule;

    //Pointer to the module the ball was in last tick
    Module *prevModule;

    direction moveDir;
} ball;

//Acceleration of 3d gravity in metres per second
point3D gravity;

//Acceleration caused by wind resistance in metres per second
float windResistance;

//Seconds since last tick
float deltaT_seconds;

void init();
void resetCourse();
void display();
void drawStartFloor();
void drawBall();
void keyboard(unsigned char key, int x, int y);
void noKeyboard(unsigned char key, int x, int y);
void animate(int value);
void addWindResistance();

#endif // MAINHEADER_H_INCLUDED
