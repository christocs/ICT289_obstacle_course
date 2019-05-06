#include "mainHeader.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <freeglut.h>
#include <cmath>

int main(int arc, char** argv)
{
    glutInit(&arc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1024,1024);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Obstacle course");

    init();

    glutDisplayFunc(display);

    glutTimerFunc(TIMERMSECS, animate, 0);


    glutMainLoop();
}

void init()
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 1000000.0);

    /*
    //Initialise modules
    3dPoint plainModulePos
    plainModulePos.x = 0
    plainModulePos.y = 0
    plainModulePos.z = 0
    PlainModule plainModule(plainModulePos)

    //Add modules to container
    moduleContainer.insert(plainModule)

    //Check modules do not have overlapping bounds
    //Todo: Implement

    display()*/

    resetCourse();

}

void resetCourse()
{
    //Define default gravity
    gravity.x = 0;
    gravity.y = -9.8;
    gravity.z = 0;

    //Define default wind resistance
    windResistance = -2;

    //Set initial time before last tick (technically 0)
    deltaT_seconds = TIMERMSECS / 1000.0;

    //Set current and previous modules to null
    ball.currentModule = nullptr;
    ball.prevModule = nullptr;

    //Set default move acceleration along an x-z plane
    ball.moveAcc = 50;

    //Set default jump acceleration
    ball.jumpAcc = 30;

    ball.radius = 100;
    ball.prevPos.x = 0;
    ball.prevPos.y = 100;
    ball.prevPos.z = 0;

    ball.currPos = ball.prevPos;

    ball.prevVel.x = 0;
    ball.prevVel.y = 0;
    ball.prevVel.z = 0;

    ball.currVel = ball.prevVel;

    ball.currTime = glutGet(GLUT_ELAPSED_TIME)/1000;
    ball.prevTime= ball.currTime;

    ball.ifDeAcceleration.x = false;
    ball.ifDeAcceleration.y  = false;
    ball.ifDeAcceleration.z = false;
}


void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Look at the ball's current position
    gluLookAt((ball.currPos.x), (ball.currPos.y + 1000), (ball.currPos.z-1000), (ball.currPos.x), (ball.currPos.y), (ball.currPos.z), 0, 1, 0);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    drawStartFloor();
    drawBall();


    /*
    //Call display functions for each module
    for (i = 0; i < moduleContainer.length; i++) {
    	moduleContainer[i].display()
    }*/

    glutSwapBuffers();
}


void drawStartFloor()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1000, -100,  -1000);
    glVertex3f(1000, -100, -1000);
    glVertex3f(1000, -100, 5000);
    glVertex3f(-1000, -100, 5000);
    glEnd();

}

void drawBall()
{
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix ();

    glTranslatef (ball.currPos.x,ball.currPos.y,ball.currPos.z);
    glRotatef (ball.rotationAngle, ball.rotation.x, ball.rotation.y, 0 );

    glutSolidSphere(100,100,10);
    glPopMatrix();

    //ball.rotation.x = 0;
    // ball.rotation.y = 0;
}


void animate(int value)
{
    glutTimerFunc(TIMERMSECS,animate,0);

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(noKeyboard);

    //Animate ball
    ball.currTime = glutGet(GLUT_ELAPSED_TIME)/1000;
    deltaT_seconds = ball.currTime - ball.prevTime;

    //Calc current position of ball and velocity, WIP
    //Note for acceleration need to take account ball velocity + gravity acceleration + wind resistance

    //ANOTHER NOTE removed gravity for the x and z calculations

    ball.currPos.x = ball.prevPos.x + ball.prevVel.x;

    /*if (direction.y)
    {
        ball.currPos.y = ball.prevPos.y + ball.prevVel.y * deltaT_seconds + 0.5 * gravity.y * pow(deltaT_seconds,2);
        if (ball.prevVel.y < 500)
            ball.currVel.y  = ball.prevVel * deltaT_seconds;
    }*/

    ball.currPos.z = ball.prevPos.z + ball.prevVel.z;

    deAcceleration();

    ball.prevPos = ball.currPos;
    ball.prevTime = ball.currTime;

    // Calling post redisplay calls the display again and so we don't need to draw the ball in here else it will be drawn twice
    glutPostRedisplay();
}


void deAcceleration()
{
    if (ball.ifDeAcceleration.z)
    {
        ball.prevVel.z = ball.prevVel.z / 1.2 ;

        if ((ball.prevVel.z < 0.5 && ball.prevVel.z > 0) || (ball.prevVel.z > -0.5 && ball.prevVel.z < 0))
            ball.prevVel.z  = 0;

        if (ball.prevVel.z == 0)
            ball.ifDeAcceleration.z = false;
    }

    if (ball.ifDeAcceleration.x)
    {
        ball.prevVel.x = ball.prevVel.x / 1.2 ;

        if ((ball.prevVel.x < 0.5 && ball.prevVel.x > 0) || (ball.prevVel.x > -0.5 && ball.prevVel.x < 0))
            ball.prevVel.x  = 0;

        if (ball.prevVel.x == 0)
             ball.ifDeAcceleration.x = false;
    }

}

void keyboard(unsigned char key, int x, int y)
{
    if(key == 'a' )
    {
        if (ball.prevVel.x < 50 && ball.prevVel.x >=0)
        {

            if  (ball.prevVel.x == 0)
            {
                ball.prevVel.x = 0.1;
                ball.rotationAngle = 1;
            }

                ball.prevVel.x = ball.prevVel.x * 1.5 ;

        }

        ball.rotation.y = 2;
        ball.rotationAngle = ball.rotationAngle * 1.5;
    }

    if(key == 'd' )
    {
        if (ball.prevVel.x > -50 && ball.prevVel.x <=0 )
        {

            if  (ball.prevVel.x == 0)
            {
                ball.prevVel.x = -0.5;
                ball.rotationAngle = -2;
            }

                ball.prevVel.x = ball.prevVel.x * 1.5;
        }

        ball.rotation.y = 2;
        ball.rotationAngle = ball.rotationAngle * 1.5;
    }

    if(key == 'w' )
    {
        if (ball.prevVel.z < 50 && ball.prevVel.z >=0)
        {

            if  (ball.prevVel.z == 0)
            {
                ball.prevVel.z = 0.1;
                ball.rotationAngle = 1;
            }

                ball.prevVel.z = ball.prevVel.z * 1.5 ;

        }

        ball.rotation.x = 2;
        ball.rotationAngle = ball.rotationAngle * 1.5;
    }


    if(key == 's' )
    {
        if (ball.prevVel.z > -50 && ball.prevVel.z <=0 )
        {

            if  (ball.prevVel.z == 0)
            {
                ball.prevVel.z = -0.5;
                ball.rotationAngle = -2;
            }

                ball.prevVel.z = ball.prevVel.z * 1.5;
        }

        ball.rotation.x = 2;
        ball.rotationAngle = ball.rotationAngle * 1.5;
    }


    if(key == 'q' )
    {
        resetCourse();
    }

}

void noKeyboard(unsigned char key, int x, int y)
{
    if(key == 'd' )
    {
        ball.ifDeAcceleration.x = true;
    }

    if(key == 'a' )
    {
        ball.ifDeAcceleration.x = true;
    }

    if(key == 'w' )
    {
        ball.ifDeAcceleration.z = true;
    }

     if(key == 's' )
    {
       ball.ifDeAcceleration.z = true;
    }

}

