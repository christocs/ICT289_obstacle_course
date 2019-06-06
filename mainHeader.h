#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <GL/freeglut.h>
#include "ball.h"
#include "point3D.h"
#include <vector>
#include <fstream>

#include "Object.h"
#include "BasicPlatform.h"
#include "Coin.h"
#include "XMovingPlatform.h"
#include "TempPlatform.h"
#include "YMovingPlatform.h"

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

#define WIND_X_VAL 3

#define DEFAULT_PLAT_DEPTH 900

#define X_MOVING_PLATFORM_MOVE_SPEED 1
#define X_MOVING_PLATFORM_MOVE_DISTANCE 3000

#define Y_MOVING_PLATFORM_MOVE_SPEED 1
#define Y_MOVING_PLATFORM_MOVE_DISTANCE 1500

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

#define   I_HEIGHT	320
#define   I_WIDTH 	240
FILE *cFile, *kFile, *rFile;
typedef 	unsigned char	pixel;
pixel	imageBuffer[I_HEIGHT*I_WIDTH];
pixel	imageBufferC[I_HEIGHT*I_WIDTH];
pixel	imageBufferK[I_HEIGHT*I_WIDTH];
pixel	imageBufferR[I_HEIGHT*I_WIDTH];
pixel 	imageR[I_HEIGHT][I_WIDTH];
pixel 	imageC[I_HEIGHT][I_WIDTH];
pixel 	imageK[I_HEIGHT][I_WIDTH];
int charin, row, column;
int cCharIn,rCharIn,kCharIn;
bool stop=false;

void loadImage();
void dispImages();
void exitProg(int x);
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
BasicPlatform plat3(-1000, 1000, -100, 13000, 14200, DEFAULT_PLAT_DEPTH, 0, 0);
BasicPlatform sidePlat1(1600, 2400, -100, 4500, 5000, DEFAULT_PLAT_DEPTH, 0, 0);
BasicPlatform sidePlat2(-2400, -1600, 100, 9250, 9750, DEFAULT_PLAT_DEPTH, 0, 0);

Coin coin1(2000, 0, 4750, 50);
Coin coin2(-2000, 200, 9500, 50);

Coin coin3(-800, 0, 13400, 50);
Coin coin4(-400, 0, 13400, 50);
Coin coin5(0, 0, 13400, 50);
Coin coin6(400, 0, 13400, 50);
Coin coin7(800, 0, 13400, 50);
Coin coin8(-800, 0, 13800, 50);
Coin coin9(-400, 0, 13800, 50);
Coin coin10(0, 0, 13800, 50);
Coin coin11(400, 0, 13800, 50);
Coin coin12(800, 0, 13800, 50);

XMovingPlatform xMovPlat1(-500, 500, -100, 6000, 7000, DEFAULT_PLAT_DEPTH, 0, 0, X_MOVING_PLATFORM_MOVE_DISTANCE, X_MOVING_PLATFORM_MOVE_SPEED, true);
XMovingPlatform xMovPlat2(-500, 500, -100, 7400, 8400, DEFAULT_PLAT_DEPTH, 0, 0, X_MOVING_PLATFORM_MOVE_DISTANCE, X_MOVING_PLATFORM_MOVE_SPEED, false);
XMovingPlatform xMovPlat3(-500, 500, -100, 11000, 12000, DEFAULT_PLAT_DEPTH, 0, 0, X_MOVING_PLATFORM_MOVE_DISTANCE, X_MOVING_PLATFORM_MOVE_SPEED, false);

TempPlatform tempPlat1(-500, 500, 100, 9000, 10000, 500, 0, 0, 1500);

YMovingPlatform yMovPlat1(-350, 350, 300, 8600, 8800, 800, 0, 0, Y_MOVING_PLATFORM_MOVE_DISTANCE, Y_MOVING_PLATFORM_MOVE_SPEED, true);
YMovingPlatform yMovPlat2(-350, 350, 300, 10200, 10400, 800, 0, 0, Y_MOVING_PLATFORM_MOVE_DISTANCE, Y_MOVING_PLATFORM_MOVE_SPEED, false);

//Pointers to game objects
std::vector<Object*> objects;

#endif // MAINHEADER_H
