#ifndef MODULEONETEST_H_INCLUDED
#define MODULEONETEST_H_INCLUDED
#include <iostream>
#include <GL/freeglut.h>
#include "point3D.h"
#include "YAlignedPlane.h"
#include "XAlignedPlane.h"
#include "ZAlignedPlane.h"


class moduleOneTest
{
    public:
        moduleOneTest();
        ~moduleOneTest();
        point3D startModuleOne(point3D tempBallPos, point3D gravityTemp, float radiusTemp);
        const point3D *getPlaneSize();

    private:
        void animatePlanes();

        void detectBallLocation();

        void drawPlatOne();
        void drawPlatTwo();
        void drawPlatThree();
        void drawPlatFour();
        void drawPlatFive();
        void drawPlatSix();
        void drawPlatSeven();
        void drawPlatEight();
        void drawPlatNine();
        void drawPlatTen();
        void drawPlatEleven();

        // Size of the planes
        point3D plane[4];
        point3D movingBox[4];
        point3D movingBox2[4];
        point3D dangerBox[4];
        point3D plane6[4];
        point3D movingBox3[4];
        point3D movingBox4[4];
        point3D plane10[4];
        point3D plane11[4];

        // Whether or not the moving platforms move left or right
        bool moveLeft = true;

        // Whether or not the wall moves left or right
        bool moveWall = true;

        // Bounds Checking of the platforms and the ball
        point3D ballPos;
        point3D gravityLocal;

        float rLocal = 0;

        //Enable falling platform
        bool fall = false;
        bool firstLand = true;
        bool colourCounter = false;
        int fallCounter = true;

        //Checks to see if a coin has been collected
        bool collectOne = true;
        bool collectTwo = true;
        //total score
        int score = 0;
};

#endif // MODULEONETEST_H_INCLUDED
