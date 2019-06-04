#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <freeglut.h>
#include "Module.h"
#include "ball.h"
#include "moduleOneTest.h"

// The time in milliseconds between timer ticks
#define TIMERMSECS 9

#define PROGRAM_NAME "Obstacle Course"

//Contains information about the ball
ball ball;

//Acceleration of 3d gravity in metres per second
point3D gravity;

//Acceleration caused by wind resistance in metres per second
float windResistance;

//Seconds since last tick
float deltaT_seconds;

//Contains all modules in the course
//Module modules[];

void init();
void resetCourse();
void display();
void drawStartFloor();
void drawBall();
void keyboard(unsigned char key, int x, int y);
void noKeyboard(unsigned char key, int x, int y);
void animate(int value);
void addWindResistance();
void startPlatform();
void drawEndFloor();


//Has jump been pressed
bool jumpPress;
//The main module
moduleOneTest levelOne;

//MoonJump cheatcode
int jumpH = 1100;
bool moonJumpTrue = false;

int xWind = 0;
bool wind = false;
#endif // MAINHEADER_H_INCLUDED
