#include "mainHeader.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>


int main(int arc, char** argv)
{
    glutInit(&arc, argv);

    loadImage();

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1024,1024);
    glutInitWindowPosition(0,0);
    glutCreateWindow(PROGRAM_NAME);

    init();

    glutDisplayFunc(display);

    glutTimerFunc(TIMERMSECS, animate, 0);


    glutMainLoop();
}

void loadImage(void){

    if ( (cFile=fopen("christo.raw","rb"))==NULL ||
         (kFile=fopen("kye.raw","rb"))==NULL ||
         (rFile=fopen("rory.raw","rb"))==NULL  ){
        printf("\nError opening image, exiting...");
        exit(1);
    }

    for (row = 0; row < HEIGHT; row++){
        for(column=0; column<WIDTH;column++){

            if( (cCharIn=fgetc(cFile))==EOF ||
                (kCharIn=fgetc(kFile))==EOF ||
                (rCharIn=fgetc(rFile))==EOF ){

                printf("\nError reading image, exiting...");
                exit(1);
            }
            imageC[row][column]=cCharIn;
            imageR[row][column]=rCharIn;
            imageK[row][column]=kCharIn;
        }
    }
    printf("\nImage successfully read\n");
    fclose(cFile);
    fclose(kFile);
    fclose(rFile);

}

void init()
{
    glClearColor (0.196078, 0.6, 0.8, 1.0);
    glColor3f(1.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 1000000.0);
    glEnable (GL_DEPTH_TEST);
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
    glutSetKeyRepeat(0);

    resetCourse();

}


void startPlatform()
{
    drawStartFloor();

    gravity = levelOne.startModuleOne(ball.prevPos, gravity, ball.radius);
}

void resetCourse()
{
    //Define default gravity
    gravity.x = 0;
    gravity.y = 0;
    gravity.z = 0;

    //Define default wind resistance
    windResistance = 0.35;

    //Set initial time before last tick (technically 0)
    deltaT_seconds = TIMERMSECS / 1000.0;

    //Set default move acceleration along an x-z plane
    ball.moveAcc = 0.2;

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
    if(!stop){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //Look at the ball's current position
        gluLookAt((ball.currPos.x), (ball.currPos.y + 1000), (ball.currPos.z-1000), (ball.currPos.x), (ball.currPos.y), (ball.currPos.z), 0, 1, 0);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        startPlatform();
        drawStartFloor();
        drawBall();

        /*
        //Call display functions for each module
        for (i = 0; i < moduleContainer.length; i++) {plane[0].x,plane[0].y,  plane[0].z
            moduleContainer[i].display()
        }*/

        if (ball.currPos.y < -2500)
            resetCourse();

        glutSwapBuffers();
    }
}


void drawStartFloor()
{
    glColor3f(.48235, 0.98823, 0.0);

    glBegin(GL_POLYGON);
        glVertex3f(-500, -100,  -100);
        glVertex3f(500, -100, -100);
        glVertex3f(500, -100, 1000);
        glVertex3f(-500, -100, 1000);
    glEnd();

    /*if (ball.prevPos.x - ball.radius >= -500 && ball.prevPos.x- ball.radius <= 500 && ball.prevPos.z - ball.radius  >= -100 && ball.prevPos.z - ball.radius  <= 1000 && ball.prevPos.y >= 100 && ball.prevPos.y <= 100.1)
        gravity.y = 0;

    else
        gravity.y = -0.2;/*

    glColor3f(1.0, 1.0, 0.0);

}

void drawEndFloor()
{
    /*point3D modulePlane[4] ;
    modulePlane = levelOne.getPlaneSize();

    glColor3f(1.0, 0.0, 0.0);


    glBegin(GL_POLYGON);
        glVertex3f(modulePlane[3].x/1.5, -100,  modulePlane[3].z);
        glVertex3f(modulePlane[4].x/1.5, -100, modulePlane[3].z);
        glVertex3f(modulePlane[4].x/1.5, -100, modulePlane[3].z + 250);
        glVertex3f(modulePlane[3].x/1.5, -100, modulePlane[3].z + 250);
    glEnd();

    glColor3f(1.0, 1.0, 0.0);

    glBegin(GL_POLYGON);
        glVertex3f(-250, -100,  500);
        glVertex3f(250, -100, 500);
        glVertex3f(250, -100, 750);
        glVertex3f(-250, -100, 750);
    glEnd();

    if (ball.currPos.x > modulePlane[3].x/1.5 && ball.currPos.x < modulePlane[4].x/1.5 && ball.currPos.z > modulePlane[3].z&& ball.currPos.z < modulePlane[3].z + 250)
    {
        resetCourse();
        currentModule++;
    } */


}

void drawBall()
{
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix ();

    glTranslatef (ball.currPos.x,ball.currPos.y,ball.currPos.z);
    glRotatef (ball.rotationAngle, ball.rotation.x, ball.rotation.y, ball.rotation.z );

    glutSolidSphere(ball.radius, ball.radius / 8, ball.radius / 8);
    glPopMatrix();


}


void animate(int value)
{
    if(!stop){
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
            ball.currPos.x = ball.prevPos.x + ball.currVel.x * deltaT_seconds - xWind;
            if (ball.currVel.x > 0.1 || ball.currVel.x < -0.1 )
            {
                ball.rotation.y = 1;
                ball.rotationAngle =  ball.rotationAngle + 6;
            }

            else
                ball.rotation.z = 0;

            if (gravity.z == 0)
                ball.currPos.z = ball.prevPos.z + ball.currVel.z * deltaT_seconds;

            else
                 ball.currPos.z = ball.prevPos.z - gravity.z;

            if (ball.currVel.z > 0.1 || ball.currVel.z < -0.1 )
            {
                ball.rotation.x = 1;
                ball.rotationAngle =  ball.rotationAngle + 6;
            }

            else
                ball.rotation.x = 0;


            ball.currPos.y = ball.prevPos.y + ball.currVel.y * deltaT_seconds + 0.5 * gravity.y * pow(deltaT_seconds,2.0);
            ball.currVel.y = ball.currVel.y * gravity.y;


        }

        //std::cout << "x: " << ball.currPos.x << " y: " << ball.currPos.y << " z: " << ball.currPos.z << std::endl;
        //std::cout << gravity.z << std::endl;

        ball.prevVel = ball.currVel;
        ball.prevPos = ball.currPos;
        ball.prevTime = ball.currTime;

        // Calling post redisplay calls the display again and so we don't need to draw the ball in here else it will be drawn twice
        glutPostRedisplay();
    }
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

    if (key == 32)
    {
        if (ball.prevPos.y >= 80 && ball.prevPos.y <= 120 && jumpPress == false)
        {
              ball.moveDir.posY = true;

              jumpPress = false;
        }
    }
    if (key=='p'){
        stop=true;
        dispImages();
        glutTimerFunc(5000,exitProg,0);
    }
}

void exitProg(int x){
    printf("exiting...");
    exit(1);
    }



void dispImages(){
    int offset = 0;

	for ( row = HEIGHT-1;  row >= 0;  row-- )	{
      for ( column = 0;  column < WIDTH; column++)  {
      	imageBufferC[WIDTH*offset + column] =  imageC[row][column];
      	imageBufferK[WIDTH*offset + column] =  imageK[row][column];
      	imageBufferR[WIDTH*offset + column] =  imageR[row][column];
      }
      offset++;
	}

    glClear(GL_COLOR_BUFFER_BIT);

    glBitmap(0, 0, 0, 0, 60, 342, NULL);//easier way to set raster pos using last 2 ints
	glDrawPixels(WIDTH, HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, imageBufferC);
    glBitmap(0, 0, 0, 0, 300, 0, NULL);
	glDrawPixels(WIDTH, HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, imageBufferK);
    glBitmap(0, 0, 0, 0, 300, 0, NULL);
	glDrawPixels(WIDTH, HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, imageBufferR);

	int	i;
    char	caption1[ ] = "Christo Stephenson";
    char	caption2[ ] = "Kye Horbury";
    char	caption3[ ] = "Rory Lowe-McLoughlin";

    glColor3f(0.0, 0.0, 0.0);

    glBitmap(0, 0, 0, 0,-600, -20, NULL);
    for (i=0; i< sizeof(caption1); i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, caption1[i]);

    glBitmap(0, 0, 0, 0, 138, 0, NULL);
    for (i=0; i< sizeof(caption2); i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, caption2[i]);

    glBitmap(0, 0, 0, 0, 201, 0, NULL);
    for (i=0; i< sizeof(caption3); i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, caption3[i]);

	glutSwapBuffers();
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
        //gravity.y = -9.8;
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
