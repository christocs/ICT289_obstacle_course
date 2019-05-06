#include "mainHeader.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
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
    windResistance = -0.5;

    //Set initial time before last tick (technically 0)
    deltaT_seconds = TIMERMSECS / 1000.0;

    //Set current and previous modules to null
    ball.currentModule = nullptr;
    ball.prevModule = nullptr;

    //Set default move acceleration along an x-z plane
    ball.moveAcc = 0.2;

    //Set default jump acceleration
    ball.jumpAcc = 2;

    //Set defaulta acceleration
    ball.acc.x = 0;
    ball.acc.y = 0;
    ball.acc.z = 0;

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

    /** Animate ball */
    ball.currTime = glutGet(GLUT_ELAPSED_TIME)/1000;
    deltaT_seconds = ball.currTime - ball.prevTime;

    addWindResistance();

    //Note for acceleration need to take account ball velocity + gravity acceleration + wind resistance

    /*if (direction.y)
    {
        ball.currPos.y = ball.prevPos.y + ball.prevVel.y * deltaT_seconds + 0.5 * gravity.y * pow(deltaT_seconds,2);
        if (ball.prevVel.y < 500)
            ball.currVel.y  = ball.prevVel * deltaT_seconds;
    }*/

    ball.currPos.x = ball.prevPos.x + ball.prevVel.x;
    ball.currPos.z = ball.prevPos.z + ball.prevVel.z;

    //Attempt at more realistic acceleration calculation, was very computational heavy
//    ball.currPos.z = ball.prevPos.z + ball.prevVel.z * deltaT_seconds + 0.5 * ((ball.acc.z * windResistance) * deltaT_seconds * deltaT_seconds);

    ball.prevPos = ball.currPos;
    ball.prevTime = ball.currTime;

    // Calling post redisplay calls the display again and so we don't need to draw the ball in here else it will be drawn twice
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    //Note: need to catch if delta between velocity and 0 is smaller than MAXMOVESPEED and if this is so, set velocity to 0 so the velocity direction doesn't invert
    float additionalSpeed = ball.moveAcc * TIMERMSECS;
    if(key == 'a' && ball.prevVel.x < MAXMOVESPEED)
    {
        ball.prevVel.x += additionalSpeed;

        //rotates the ball, will need to change this to rotate based on speed
        ball.rotation.y = 2;
        ball.rotationAngle = ball.rotationAngle * 1.5;
    }

    if(key == 'd' && ball.prevVel.x > -MAXMOVESPEED)
    {
        ball.prevVel.x -= additionalSpeed;

        //rotates the ball, will need to change this to rotate based on speed
        ball.rotation.y = -2;
        ball.rotationAngle = ball.rotationAngle * 1.5;
    }

    if(key == 'w' && ball.prevVel.z < MAXMOVESPEED)
    {
        ball.prevVel.z += additionalSpeed;

        //rotates the ball, will need to change this to rotate based on speed
        ball.rotation.z = 2;
        ball.rotationAngle = ball.rotationAngle * 1.5;
    }

    if(key == 's' && ball.prevVel.z > -MAXMOVESPEED)
    {
        ball.prevVel.z -= additionalSpeed;

        //rotates the ball, will need to change this to rotate based on speed
        ball.rotation.z = -2;
        ball.rotationAngle = ball.rotationAngle * 1.5;
    }

    if(key == 'q' )
    {
        resetCourse();
    }
}

void addWindResistance()
{
    //need to catch edge cases where velocity + or - wind resistance will make the velocity change directions (when the delta between the velocity and 0 is smaller than the wind resistance)
    if (ball.prevVel.x > 0) {
        ball.prevVel.x += windResistance;
    } else if (ball.prevVel.x < 0) {
        ball.prevVel.x -+ windResistance;
    }

    if (ball.prevVel.z > 0) {
        ball.prevVel.z += windResistance;
    } else if (ball.prevVel.z < 0) {
        ball.prevVel.z -+ windResistance;
    }
}
