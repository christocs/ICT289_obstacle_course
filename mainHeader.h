#ifndef MAINHEADER_H_INCLUDED
#define MAINHEADER_H_INCLUDED

   struct Direction
    {
        bool x;
        bool y;
        bool z;
    };

    //Defines a 3d point
    struct point3D
    {
        float x;
        float y;
        float z;
    };

    //Struct for ball
    struct
    {
        //Previous position of ball's centre (from last tick)
        point3D prevPos;
        //Current position of ball's centre
        point3D currPos;
        //Previous velocity of the ball (from last tick)
        point3D prevVel;

        point3D currVel;
        //Current acceleration of the ball in 3d space in metres per second
        point3D acc;

        point3D rotation;

        float rotationAngle;

        Direction direction;

        //Radius of ball in metres
        float radius;
        //mass of ball in kg
        float mass;

        float prevTime;

        float currTime;


    }ball;



//Acceleration of gravity in metres per second
point3D gravity;

//Acceleration caused by wind resistance in metres per second
float windResistance;

//Acceleration caused by making the ball move in a certain direction, usually from WASD or arrow keys
float moveAcc;

//Acceleration caused by specifically making the ball to jump, usually from pressing spacebar
float jumpAcc;

float deltaT_seconds;

void init();
void setBallStart();
void display();
void drawStartFloor();
void drawBall();
void keyboard(unsigned char key, int x, int y);
void animate(int value);
void noKeyboard(unsigned char key, int x, int y);


#endif // MAINHEADER_H_INCLUDED
