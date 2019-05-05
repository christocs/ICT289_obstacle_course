#ifndef MAINHEADER_H_INCLUDED
#define MAINHEADER_H_INCLUDED

#include "Module.h"
#include "structs.h"

// The time in milliseconds between timer ticks
#define TIMERMSECS 33

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

    //Please label what htis is
    point3D rotation;

    //Please label what this is (is it in degrees, radians, is it the current angle?)
    //What axis is the rotation on?
    float rotationAngle;

    //direction of the ball
    //Is this the current tick's direction or the previous or the next?
    Vector direction;

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

    //Acceleration caused by specifically making the ball to jump, usually from pressing spacebar
    float jumpAcc;

    //Pointer to the module the ball is currently in
    Module *currentModule;

    //Pointer to the module the ball was in last tick
    Module *prevModule;
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
void animate(int value);
void noKeyboard(unsigned char key, int x, int y);


#endif // MAINHEADER_H_INCLUDED
