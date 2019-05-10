#ifndef MAINHEADER_H
#define MAINHEADER_H

#include "Module.h"
#include "ball.h"

// The time in milliseconds between timer ticks
#define TIMERMSECS 11

//Contains information about the ball
ball ball;

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
