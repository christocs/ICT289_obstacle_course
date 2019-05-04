/** Currently pseudocode
 *	@todo: improve design
 *	@todo: replace pseudocode with c++ code
 *
 */

#include "IModule.h"

// The time in milliseconds between timer ticks
#define TIMERMSECS 33

//Acceleration of gravity in metres per second
float gravity

//Acceleration caused by wind resistance in metres per second
float windResistance 

//Acceleration caused by making the ball move in a certain direction, usually from WASD or arrow keys
float moveAcc

//Acceleration caused by specifically making the ball to jump, usually from pressing spacebar
float jumpAcc

//Defines a 3d point
struct 3dPoint {
	float x
	float y
	float z
}

//Defines a 2d point
struct 2dPoint {
	float x
	float y
}

//Defines bounds struct
struct Bounds {
	3dPoint min
	3dPoint max
}

//Struct for ball
struct {
	//Previous position of ball's centre (from last tick)
	3dPoint prevPos
	//Current position of ball's centre
	3dPoint currPos
	//Previous velocity of the ball (from last tick)
	3dPoint prevVel
	//Time of the last tick
	Time prevTime
	//Current acceleration of the ball in 3d space in metres per second
	3dPoint acc
	//Radius of ball in metres
	float radius
	//mass of ball in kg
	float mass
} ball


//Pointer to module the ball is currently in
Module *currentModule
//Pointer to module the ball was in last tick
Module *prevModule