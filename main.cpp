#include "mainHeader.h"
#include <moduleOneTest.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>



int main(int arc, char** argv)
{
    glutInit(&arc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1024,1024);
    glutInitWindowPosition(0,0);
    glutCreateWindow(PROGRAM_NAME);

    init();

    startPlatform();

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


void startPlatform()
{
    drawStartFloor();

    if (currentModule == 0)
    {
        // Display module one
        drawEndFloor();
    }

    else if (currentModule == 1)
        // Display module two


}

void resetCourse()
{
    //Define default gravity
    gravity.x = 0;
    gravity.y = -0.2;
    gravity.z = 0;

    //Define default wind resistance
    windResistance = 0.2;

    //Set initial time before last tick (technically 0)
    deltaT_seconds = TIMERMSECS / 1000.0;

    //Set current and previous modules to null
    ball.currentModule = nullptr;
    ball.prevModule = nullptr;

    //Set default move acceleration along an x-z plane
    ball.moveAcc = 1;

    //Maximum speed the ball can reach from only pressing move keys
    ball.maxMoveSpeed = 10;

    //Set default jump acceleration
    ball.jumpAcc = 0.6;

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

    ball.currTime = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    ball.prevTime= ball.currTime;

    ball.moveDir.posX = false;
    ball.moveDir.negX = false;
    ball.moveDir.posY = false;
    ball.moveDir.negY = false;
    ball.moveDir.posZ = false;
    ball.moveDir.negZ = false;
    glutIgnoreKeyRepeat(1);
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
        glVertex3f(-500, -100,  -100);
        glVertex3f(500, -100, -100);
        glVertex3f(500, -100, 1000);
        glVertex3f(-500, -100, 1000);
    glEnd();

    glColor3f(1.0, 1.0, 0.0);

}

void drawEndFloor()
{
    point3D modulePlane[4] = levelOne.getPlaneSize();

    glColor3f(1.0, 0.0, 0.0);


    glBegin(GL_POLYGON);
        glVertex3f(modulePlane[3].x/1.5, -100,  modulePlane[3].z);
        glVertex3f(modulePlane[4].x/1.5, -100, modulePlane[3].z);
        glVertex3f(modulePlane[4].x/1.5, -100, modulePlane[3].z + 250);
        glVertex3f(modulePlane[3].x/1.5, -100, modulePlane[3].z + 250);
    glEnd();

    glColor3f(1.0, 1.0, 0.0);

    /*glBegin(GL_POLYGON);
        glVertex3f(-250, -100,  500);
        glVertex3f(250, -100, 500);
        glVertex3f(250, -100, 750);
        glVertex3f(-250, -100, 750);
    glEnd();*/

    if (ball.currPos.x > modulePlane[3].x/1.5 && ball.currPos.x < modulePlane[4].x/1.5 && ball.currPos.z > modulePlane[3].z&& ball.currPos.z < modulePlane[3].z + 250)
    {
        resetCourse();
        currentModule++;
    }


}

void drawBall()
{
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix ();

    glTranslatef (ball.currPos.x,ball.currPos.y,ball.currPos.z);
    glRotatef (ball.rotationAngle, ball.rotation.x, ball.rotation.y, 0 );

    glutSolidSphere(ball.radius, ball.radius / 8, ball.radius / 8);
    glPopMatrix();

    //ball.rotation.x = 0;
    // ball.rotation.y = 0;
}


void animate(int value)
{
    glutTimerFunc(TIMERMSECS,animate,0);

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(noKeyboard);

    ball.currTime = glutGet(GLUT_ELAPSED_TIME);
    deltaT_seconds = ball.currTime - ball.prevTime;

    //calc velocity of where the ball wants to go
    ball.currVel.x = ball.prevVel.x; //add gravity here later
    //ball.currVel.x += ball.acc.x * deltaT_seconds;
    ball.currVel.z = ball.prevVel.z; //add gravity here later
    //ball.currVel.z += ball.acc.z * deltaT_seconds;
    //Implement the same for y value here and calculate for gravity

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
        ball.currVel.z += ball.moveAcc * deltaT_seconds;
    }
    if (ball.moveDir.negZ == true && ball.currVel.z > -ball.maxMoveSpeed)
    {
        ball.currVel.z -= ball.moveAcc * deltaT_seconds;
    }

    if (ball.moveDir.posY == true && ball.currVel.y < ball.maxMoveSpeed)
    {
        ball.currVel.y += ball.jumpAcc * deltaT_seconds;

    }

    addWindResistance();

    //Note for acceleration need to take account ball velocity + gravity acceleration + wind resistance

    /*if (direction.y)
    {
        ball.currPos.y = ball.prevPos.y + ball.prevVel.y * deltaT_seconds + 0.5 * gravity.y * pow(deltaT_seconds,2);
        if (ball.prevVel.y < 500)
            ball.currVel.y  = ball.prevVel * deltaT_seconds;
    }*/

    //determine current module here

    if (ball.currentModule != nullptr)
    {
        //determines ball physics, position, velocity, etc.
        //ball.currentModule.onTickInModule();
    }
    else
    {
        //determine what happens if ball is out of module
        ball.currPos.x = ball.prevPos.x + ball.currVel.x * deltaT_seconds;
        ball.currPos.z = ball.prevPos.z + ball.currVel.z * deltaT_seconds;

        if (ball.currPos.y - ball.radius > 0)
        {
            ball.currPos.y = ball.prevPos.y + ball.currVel.y * deltaT_seconds + 0.5 * gravity.y * pow(deltaT_seconds,2.0);
            ball.currVel.y = ball.currVel.y * gravity.y/10;
        }

        else
        {
             ball.currPos.y = ball.prevPos.y + ball.prevVel.y * deltaT_seconds;
        }

    }

    std::cout << "x: " << ball.currPos.x << " y: " << ball.currPos.y << " z: " << ball.currPos.z << std::endl;

    ball.prevVel = ball.currVel;
    ball.prevPos = ball.currPos;
    ball.prevTime = ball.currTime;

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

    if(key == 'q')
    {
        resetCourse();
    }

    if (key == 32)
    {
        if (ball.currPos.y - ball.radius <= 0.1 && jumpPress == false)
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

    if (key == 32)
    {
        ball.moveDir.posY = false;
    }

}

void addWindResistance()
{
    //need to catch edge cases where velocity + or - wind resistance will make the velocity change directions (when the delta between the velocity and 0 is smaller than the wind resistance)
    if (ball.currVel.x > 0)
    {
        ball.currVel.x *= windResistance;
    }
    else if (ball.currVel.x < 0)
    {
        ball.currVel.x *= windResistance;
    }

    if (ball.currVel.z > 0)
    {
        ball.currVel.z *= windResistance;
    }
    else if (ball.currVel.z < 0)
    {
        ball.currVel.z *= windResistance;
    }
}
