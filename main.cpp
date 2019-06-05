#include "mainHeader.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

int main(int arc, char** argv)
{
    glutInit(&arc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0,0);
    glutCreateWindow(PROGRAM_NAME);

    init();

    glutDisplayFunc(display);

    glutTimerFunc(TIMERMSECS, animate, 0);

    glutMainLoop();
}

void init()
{
    glClearColor(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, BACKGROUND_A);
    glColor3f(DEFAULT_R, DEFAULT_G, DEFAULT_B);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, WINDOW_WIDTH / (float) WINDOW_HEIGHT, NEAR_VAL, FAR_VAL);
    glEnable(GL_DEPTH_TEST);

    glutSetKeyRepeat(0);

    objects.push_back(&startPlatform);

    resetCourse();
}

void resetCourse()
{
    //Set initial time before last tick (technically 0)
    deltaT_seconds = 0;

    ball.currTime = glutGet(GLUT_ELAPSED_TIME);
    ball.prevTime = ball.currTime;

    std::cout << "Course reset!" << std::endl;
    //Define default wind resistance
    windResistance = 0.35;

    //Set default move acceleration along an x-z plane
    ball.moveAcc = 5;

    //Maximum speed the ball can reach from only pressing move keys
    ball.maxMoveSpeed = 10;

    //Set default jump acceleration
    ball.jumpAcc = 0.6;

    //Set defaulta acceleration
    ball.acc.x = 0;
    ball.acc.y = GRAVITY_ACC;
    ball.acc.z = 0;

    ball.radius = 100;
    ball.prevPos.x = 0;
    ball.prevPos.y = 300;
    ball.prevPos.z = 0;

    ball.currPos = ball.prevPos;

    ball.prevVel.x = 0;
    ball.prevVel.y = 0;
    ball.prevVel.z = 0;

    ball.currVel = ball.prevVel;

    ball.moveDir.posX = false;
    ball.moveDir.negX = false;
    ball.moveDir.posY = false;
    ball.moveDir.negY = false;
    ball.moveDir.posZ = false;
    ball.moveDir.negZ = false;

    glutIgnoreKeyRepeat(1);

    //Reset game objects
    for (unsigned i = 0; i < objects.size(); i++)
    {
        objects[i]->reset();
    }
}


void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Look at the ball's current position
    gluLookAt((ball.currPos.x), (ball.currPos.y + 1000), (ball.currPos.z - 1000), (ball.currPos.x), (ball.currPos.y), (ball.currPos.z), 0, 1, 0);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    drawBall();

    //Display game objects
    for (unsigned i = 0; i < objects.size(); i++)
    {
        objects[i]->display();
    }

    glutSwapBuffers();
}

void drawBall()
{
    glColor3f(BALL_R, BALL_G, BALL_B);
    glPushMatrix ();

    glTranslatef (ball.currPos.x,ball.currPos.y,ball.currPos.z);
    glRotatef (ball.rotationAngle, ball.rotation.x, ball.rotation.y, ball.rotation.z );

    glutSolidSphere(ball.radius, ball.radius / 8, ball.radius / 8);
    glPopMatrix();
}


void animate(int value)
{
    glutTimerFunc(TIMERMSECS,animate,0);

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(noKeyboard);

    //Animate game objects
    for (unsigned i = 0; i < objects.size(); i++)
    {
        objects[i]->animate();
    }

    ball.currTime = glutGet(GLUT_ELAPSED_TIME);
    deltaT_seconds = ball.currTime - ball.prevTime;

    //Apply ball acceleratino to velocity
    ball.currVel.x = ball.prevVel.x;
    ball.currVel.x += ball.acc.x * deltaT_seconds;
    ball.currVel.y = ball.prevVel.y;
    ball.currVel.y += ball.acc.y * deltaT_seconds;
    ball.currVel.z = ball.prevVel.z;
    ball.currVel.z += ball.acc.z * deltaT_seconds;

    //add acceleration onto velocity when keys pressed
    if (ball.moveDir.posX == true && ball.currVel.x < ball.maxMoveSpeed)
    {
        ball.currVel.x += ball.moveAcc * deltaT_seconds;
    }
    if (ball.moveDir.negX == true && ball.currVel.x > -ball.maxMoveSpeed)
    {
        ball.currVel.x -= ball.moveAcc * deltaT_seconds;
    }
    if (ball.moveDir.posZ == true && ball.currVel.z < ball.maxMoveSpeed)
    {
        ball.currVel.z += ball.moveAcc * deltaT_seconds ;
    }
    if (ball.moveDir.negZ == true && ball.currVel.z > -ball.maxMoveSpeed)
    {
        ball.currVel.z -= ball.moveAcc * deltaT_seconds;
    }

    if (ball.moveDir.posY == true && ball.currVel.y < ball.maxMoveSpeed)
    {
        ball.currVel.y += ball.jumpAcc * deltaT_seconds;

    }

    if (ball.prevPos.y >= jumpH)
    {
        ball.jumpAcc = 0;
    }

    /* else if  (ball.prevPos.y > 120 && ball.prevPos.y  < jumpH)
     {
         ball.currVel.y -= 0.1;
     }*/

    else if (ball.prevPos.y >= 80 && ball.prevPos.y <= 120 )
    {
        ball.jumpAcc = 0.6;
    }

    addWindResistance(ball.currVel);

    float millisecondsPassed = deltaT_seconds / (float) TIMERMSECS;

    //If ball moving in x direction, rotate
    if (ball.currVel.x > 0.1 || ball.currVel.x < -0.1 )
    {
        ball.rotation.y = millisecondsPassed;
        ball.rotationAngle =  ball.rotationAngle + 6 * millisecondsPassed;
    }
    else
    {
        ball.rotation.z = 0;
    }

    //If ball moving z direction, rotate
    if (ball.currVel.z > 0.1 || ball.currVel.z < -0.1 )
    {
        ball.rotation.x = millisecondsPassed;
        ball.rotationAngle =  ball.rotationAngle + 6 * millisecondsPassed;
    }
    else
    {
        ball.rotation.x = 0;
    }

    /* Determine altered velocity from collisions */
    int collisions = 0;

    //Average velocity from collisions
    point3D colVel;
    colVel.x = 0;
    colVel.y = 0;
    colVel.z = 0;
    //Temporary velocity store for processing
    point3D tempVel;

    for (unsigned i = 0; i < objects.size(); i++)
    {
        if (objects[i]->collisionDetected(ball.currVel, ball.prevPos, ball.radius))
        {
            tempVel = objects[i]->getBallVel(ball.currVel, ball.prevPos, ball.radius);
            colVel.x += tempVel.x;
            colVel.y += tempVel.y;
            colVel.z += tempVel.z;

            collisions++;
        }
    }

    //Calc average velocity of collisions and change velocity of ball if collisions happened
    if (collisions > 0)
    {
        //Determine average
        colVel.x /= (float) collisions;
        colVel.y /= (float) collisions;
        colVel.z /= (float) collisions;

        //Modify velocity
        ball.currVel.x = colVel.x;
        ball.currVel.y = colVel.y;
        ball.currVel.z = colVel.z;
    }

    /* ensure velocity never reaches over a maximum */
    if (ball.currVel.x > MAX_VEL)
    {
        ball.currVel.x = MAX_VEL;
    }
    else if (ball.currVel.x < -MAX_VEL)
    {
        ball.currVel.x = -MAX_VEL;
    }

    if (ball.currVel.y > MAX_VEL)
    {
        ball.currVel.y = MAX_VEL;
    }
    else if (ball.currVel.y < -MAX_VEL)
    {
        ball.currVel.y = -MAX_VEL;
    }

    if (ball.currVel.z > MAX_VEL)
    {
        ball.currVel.z = MAX_VEL;
    }
    else if (ball.currVel.z < -MAX_VEL)
    {
        ball.currVel.z = -MAX_VEL;
    }

    if (ball.currVel.y < JITTER_VEL && ball.currVel.y > -JITTER_VEL)
    {
        ball.currVel.y = 0;
    }
    std::cout << (ball.currVel.y < JITTER_VEL && ball.currVel.y > -JITTER_VEL) << std::endl;


    ball.currPos.x = ball.prevPos.x + ball.currVel.x;
    ball.currPos.y = ball.prevPos.y + ball.currVel.y;
    ball.currPos.z = ball.prevPos.z + ball.currVel.z;

    ball.prevVel = ball.currVel;
    ball.prevPos = ball.currPos;
    ball.prevTime = ball.currTime;

    std::cout << ball.currVel.x << " " << ball.currVel.y << " " << ball.currVel.z << std::endl;

    //Reset course if ball's height goes too low
    if (ball.currPos.y < MINIMUM_Y_VALUE_RESET_ZONE)
        resetCourse();

    // Calling post redisplay calls the display again and so we don't need to draw the ball in here else it will be drawn twice
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if(key == 'a')
    {
        ball.moveDir.posX = true;
    }

    if(key == 'd')
    {
        ball.moveDir.negX = true;
    }

    if(key == 'w')
    {
        ball.moveDir.posZ = true;
    }

    if(key == 's')
    {
        ball.moveDir.negZ = true;
    }

    if(key == 'm')
    {
        if (!moonJumpTrue)
        {
            jumpH = 3000;
            moonJumpTrue = true;
        }

        else
        {
            jumpH = 1100;
            moonJumpTrue = false;
        }
    }

    if(key == 'n')
    {
        if (!wind)
        {
            xWind = -20;
            wind = true;
        }
        else
        {
            xWind = 0;
            wind = false;
        }
    }

    if(key == 'q')
    {
        resetCourse();
    }

    //Detects if spacebar is pressed
    if (key == 32)
    {
        if (ball.prevPos.y >= 80 && ball.prevPos.y <= 120 && jumpPress == false)
        {
            ball.moveDir.posY = true;

            jumpPress = false;
        }
    }
}

void noKeyboard(unsigned char key, int x, int y)
{
    if(key == 'a')
    {
        ball.moveDir.posX = false;
    }

    if(key == 'd')
    {
        ball.moveDir.negX = false;
    }

    if(key == 'w')
    {
        ball.moveDir.posZ = false;
    }

    if(key == 's')
    {
        ball.moveDir.negZ = false;
    }

    //Detects if spacebar is not pressed
    if (key == 32)
    {
        ball.moveDir.posY = false;
    }

}

void addWindResistance(point3D& vel)
{
    float millisecondsPassed = deltaT_seconds / (float) TIMERMSECS;
    if (vel.x > 0)
    {
        vel.x *= WIND_COEFFICIENT * millisecondsPassed;
    }
    else if (vel.x < 0)
    {
        vel.x *= WIND_COEFFICIENT * millisecondsPassed;
    }

    if (vel.y > 0)
    {
        vel.y *= WIND_COEFFICIENT * millisecondsPassed;
    }
    else if (vel.y < 0)
    {
        vel.y *= WIND_COEFFICIENT * millisecondsPassed;
    }

    if (vel.z > 0)
    {
        vel.z *= WIND_COEFFICIENT * millisecondsPassed;
    }
    else if (vel.z < 0)
    {
        vel.z *= WIND_COEFFICIENT * millisecondsPassed;
    }
}
