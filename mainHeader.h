#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <GL/freeglut.h>
#include "ball.h"
#include "point3D.h"
#include <vector>

#include "Object.h"
#include "BasicPlatform.h"
#include "Coin.h"
#include "XMovingPlatform.h"

//The time in milliseconds between timer ticks
#define TIMERMSECS 11
//The minimum y-coordinate the ball's centre can be at before the course resets
#define MINIMUM_Y_VALUE_RESET_ZONE -2500
//Name of the program to be displayed
#define PROGRAM_NAME "Obstacle Course"
//Wind resistance coefficient to ball's velocity every millisecond
#define WIND_COEFFICIENT 0.35
//Acceleration of gravity
#define GRAVITY_ACC -2
//Default jump acceleration
#define DEFAULT_JUMP_ACC 10

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

//Jump height when moon jump cheat code is activated
#define MOON_JUMP_HEIGHT 3000
//Default jump height
#define DEFAULT_JUMP_HEIGHT 1100

//Default bounce coefficient
#define DEFAULT_BOUNCE 0.8

//Maximum velocity of the ball in any direction
#define MAX_VEL 99999

#define WIND_X_VAL 20

#define DEFAULT_PLAT_DEPTH 900

#define X_MOVING_PLATFORM_MOVE_SPEED 1
#define X_MOVING_PLATFORM_MOVE_DISTANCE 3000

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

//MoonJump cheatcode
bool moonJumpTrue = false;

bool wind = false;

/* Game objects initialisation */
BasicPlatform startPlatform(-500, 500, -100, -100, 1000, DEFAULT_PLAT_DEPTH, 0, 0);
BasicPlatform plat1(-400, 400, -100, 1000, 3500, DEFAULT_PLAT_DEPTH, 0, 0);
BasicPlatform plat2(-400, 400, -100, 4500, 5000, DEFAULT_PLAT_DEPTH, 0, 0);
BasicPlatform sidePlat1(1600, 2400, -100, 4500, 5000, DEFAULT_PLAT_DEPTH, 0, 0);

Coin coin1(2000, 0, 4850, 50);

XMovingPlatform xMovPlat1(-600, 600, -100, 6000, 7200, DEFAULT_PLAT_DEPTH, 0, 0, X_MOVING_PLATFORM_MOVE_DISTANCE, X_MOVING_PLATFORM_MOVE_SPEED, true);
XMovingPlatform xMovPlat2(-600, 600, -100, 7800, 9000, DEFAULT_PLAT_DEPTH, 0, 0, X_MOVING_PLATFORM_MOVE_DISTANCE, X_MOVING_PLATFORM_MOVE_SPEED, false);

//Pointers to game objects
std::vector<Object*> objects;

#endif // MAINHEADER_H
