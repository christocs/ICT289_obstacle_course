#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <GL/freeglut.h>
#include "ball.h"
#include "point3D.h"
#include <vector>

#include "Object.h"
#include "BasicPlatform.h"

//The time in milliseconds between timer ticks
#define TIMERMSECS 2
//The minimum y-coordinate the ball's centre can be at before the course resets
#define MINIMUM_Y_VALUE_RESET_ZONE -2500
//Name of the program to be displayed
#define PROGRAM_NAME "Obstacle Course"
//Wind resistance coefficient to ball's velocity every millisecond
#define WIND_COEFFICIENT 0.35
//Acceleration of gravity
#define GRAVITY_ACC -0.5

//Colour values
#define BALL_R 0
#define BALL_G 0
#define BALL_B 1

#define BACKGROUND_R 0.196078
#define BACKGROUND_G 0.6
#define BACKGROUND_B 0.8
#define BACKGROUND_A 1

#define DEFAULT_R 1
#define DEFAULT_G 0
#define DEFAULT_B 0

//Default bounce coefficient
#define DEFAULT_BOUNCE 0.8

//Camera values
#define FOV 60
#define NEAR_VAL 0.1
#define FAR_VAL 999999
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//Contains information about the ball
ball ball;

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
void addWindResistance(point3D& vel);
void drawEndFloor();

//Has jump been pressed
bool jumpPress;

//MoonJump cheatcode
int jumpH = 1100;
bool moonJumpTrue = false;

int xWind = 0;
bool wind = false;

//Pointer to game objects
std::vector<Object*> objects;

BasicPlatform startPlatform(-500, 500, -100, -100, 1000, 50, DEFAULT_BOUNCE, DEFAULT_BOUNCE);

#endif // MAINHEADER_H
