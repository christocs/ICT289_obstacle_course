#include "moduleOneTest.h"

moduleOneTest::moduleOneTest()
{

        gravityLocal.y = 0;
        gravityLocal.z = 0;

        plane[0].x = -400; plane[0].y = -100; plane[0].z = 1000;
        plane[1].x = 400; plane[1].y = -100; plane[1].z = 3500;
        plane[2].x = 400; plane[2].y = -100; plane[2].z = 3500;

        movingBox[0].x = -400;  movingBox[0].y = -100;  movingBox[0].z = 6500;
        movingBox[1].x = 400;  movingBox[1].y = -200;  movingBox[1].z = 7500;

        movingBox2[0].x = -400;  movingBox2[0].y = -100;  movingBox2[0].z = 8500;
        movingBox2[1].x = 400;  movingBox2[1].y = -200;  movingBox2[1].z = 9500;

        dangerBox[0].x = -500;  dangerBox[0].y = -100;  dangerBox[0].z = 10500;
        dangerBox[1].x = 500;  dangerBox[1].y = -200;  dangerBox[1].z = 11500;

        plane6[0].x = -400;   plane6[0].y = -100;   plane6[0].z = 12500;
        plane6[1].x = 400;   plane6[1].y = -200;   plane6[1].z = 13500;

        movingBox3[0].x = -700;  movingBox3[0].y = -200;  movingBox3[0].z = 14500;
        movingBox3[1].x = 700;  movingBox3[1].y = 900;  movingBox3[1].z = 14600;

        movingBox4[0].x = -500;  movingBox4[0].y = -100;  movingBox4[0].z = 14700;
        movingBox4[1].x = 500;  movingBox4[1].y = -200;  movingBox4[1].z = 15500;

        plane10[0].x = -700;   plane10[0].y = -100;   plane10[0].z = 15500;
        plane10[1].x = 700;   plane10[1].y = -200;   plane10[1].z = 17500;


        plane11[0].x = -1600;   plane11[0].y = -100;   plane11[0].z = 10500;
        plane11[1].x = -2400;   plane11[1].y = -200;   plane11[1].z = 11500;
}

moduleOneTest::~moduleOneTest()
{

}

const point3D* moduleOneTest::getPlaneSize()
{
    return plane;
}


point3D moduleOneTest::startModuleOne(point3D tempBallPos, point3D gravityTemp, float radiusTemp)
{

    ballPos = tempBallPos;
    gravityLocal.y = gravityTemp.y;
    rLocal = radiusTemp;


    animatePlanes();
    detectBallLocation();
    drawPlatOne();
    drawPlatTwo();
    drawPlatThree();
    drawPlatFour();
    drawPlatFive();

    if (!fall)
        drawPlatSix();

    drawPlatSeven();
    drawPlatEight();
    drawPlatNine();
    drawPlatTen();
    drawPlatEleven();

    return gravityLocal;
}

void moduleOneTest::animatePlanes()
{
    /**
    If any object moves, change the values here to be sent to the aligned plane. For example

    for (int i = 0; i < size of boxArray; i++)
    {
        movingBox[i] = movingBox[i] + 2;
    }
    **/

    if (moveLeft)
    {
        for (int i = 0; i < 2; i++)
        {
            movingBox[i].x = movingBox[i].x - 5;
            movingBox4[i].x = movingBox4[i].x - 5;
        }

        for (int i = 0; i < 2; i++)
        {
            movingBox2[i].x = movingBox2[i].x + 10;
        }


        if (movingBox[1].x <= -1500)
            moveLeft = false;
    }

    else
    {
        for (int i = 0; i < 2; i++)
        {
            movingBox[i].x = movingBox[i].x + 5;
            movingBox4[i].x = movingBox4[i].x + 5;
        }

        for (int i = 0; i < 2; i++)
        {
            movingBox2[i].x = movingBox2[i].x - 10;

        }

        if (movingBox[1].x >= 1500)
            moveLeft = true;
    }


    if(!firstLand && !fall)
    {
        fallCounter++;

        if (fallCounter % 14 == 0)
            colourCounter = true;

        else if (fallCounter % 7 == 0)
            colourCounter = false;
    }

    if (fallCounter == 50)
        fall = true;



    if (moveWall)
    {
        for (int i = 0; i < 2; i++)
        {
            movingBox3[i].y = movingBox3[i].y + 30;

        }


        if (movingBox3[1].y >= 2000)
            moveWall = false;
    }

    else
    {
        for (int i = 0; i < 2; i++)
        {
            movingBox3[i].y = movingBox3[i].y - 30;
        }

        if (movingBox3[0].y <= -800)
            moveWall = true;
    }
}

void moduleOneTest::detectBallLocation()
{
    /**
    Test functions for if the ball is within the area of the object, and what velocity is placed on it. For example
    if (ballCurrPos.x - radius => movingBox[0].x || ballCurrPos.x - radius <= movingBox[1] etc... )

    Mayvbe the aligned planes do this for me?? I dunno..
    **/

    // First Platform
    if (ballPos.x - rLocal >= plane[0].x  && ballPos.x- rLocal <= plane[1].x -90 && ballPos.z - rLocal >= plane[0].z && ballPos.z - rLocal  <= plane[1].z - 90 && ballPos.y >= 80 && ballPos.y <= 120)
        gravityLocal.y = 0;

    // Start Platform
    else if (ballPos.x - rLocal >= -500 && ballPos.x - rLocal <= 500 && ballPos.z - rLocal  >= -100 && ballPos.z - rLocal  <= 1000 && ballPos.y >= 80 && ballPos.y <= 120)
        gravityLocal.y = 0;

    // Second Platform
    else if (ballPos.x - rLocal >= plane[0].x  && ballPos.x - rLocal <= plane[1].x -90 && ballPos.z - rLocal >= plane[0].z + 3300 && ballPos.z - rLocal  <= plane[1].z + 1410 && ballPos.y >= 80 && ballPos.y <= 120)
        gravityLocal.y = 0;

    //Extra platform One
    else if (ballPos.x - rLocal >= plane[0].x +2000  && ballPos.x - rLocal <= plane[1].x +1910 && ballPos.z - rLocal >= plane[0].z + 3300 && ballPos.z - rLocal  <= plane[1].z + 1410 && ballPos.y >= 80 && ballPos.y <= 120)
        gravityLocal.y = 0;

     //Third
    else if (ballPos.x - rLocal >= movingBox[0].x -200 && ballPos.x - rLocal <=  movingBox[1].x -90 && ballPos.z - rLocal >= movingBox[0].z -200 && ballPos.z - rLocal <= movingBox[1].z -90 && ballPos.y >= 80 && ballPos.y <= 120)
        gravityLocal.y = 0;

    //fourth
    else if (ballPos.x - rLocal >= movingBox2[0].x -200 && ballPos.x - rLocal <=  movingBox2[1].x-90 && ballPos.z - rLocal >= movingBox2[0].z -200 && ballPos.z - rLocal <= movingBox2[1].z -90 && ballPos.y >= 80 && ballPos.y <= 120)
        gravityLocal.y = 0;

    //fifth
    else if (ballPos.x - rLocal >= dangerBox[0].x -200 && ballPos.x - rLocal <=  dangerBox[1].x -90 && ballPos.z - rLocal >= dangerBox[0].z -200 && ballPos.z - rLocal <= dangerBox[1].z -90 && ballPos.y >= 80 && ballPos.y <= 120 && !fall)
    {
        if (firstLand == true)
            firstLand = false;

        gravityLocal.y = 0;
    }

    //sixth
    else if (ballPos.x - rLocal >= plane6[0].x  && ballPos.x - rLocal <=  plane6[1].x -90 && ballPos.z - rLocal >= plane6[0].z -200 && ballPos.z - rLocal <= plane6[1].z -90 && ballPos.y >= 80 && ballPos.y <= 120)
        gravityLocal.y = 0;

    //moving wall
    else if (ballPos.x - rLocal >= movingBox3[0].x  && ballPos.x - rLocal <= movingBox3[1].x && ballPos.y - rLocal >= movingBox3[0].y -100 && ballPos.y - rLocal <= movingBox3[1].y && ballPos.z - rLocal >= movingBox3[0].z -3 && ballPos.z - rLocal <=  movingBox3[1].z)
    {
        gravityLocal.z = -2;
        gravityLocal.y = -0.2;
    }

    //Last moving platform
    else if (ballPos.x - rLocal >= movingBox4[0].x -200 && ballPos.x - rLocal <=  movingBox4[1].x -90 && ballPos.z - rLocal >= movingBox4[0].z -200 && ballPos.z - rLocal <= movingBox4[1].z -90 && ballPos.y >= 80 && ballPos.y <= 120)
        gravityLocal.y = 0;

    //Last platform
    else if (ballPos.x - rLocal >= plane10[0].x  && ballPos.x - rLocal <=  plane10[1].x -90 && ballPos.z - rLocal >= plane10[0].z -200 && ballPos.z - rLocal <= plane10[1].z -90 && ballPos.y >= 80 && ballPos.y <= 120)
        gravityLocal.y = 0;

    //Second bonus platform
    else if (ballPos.x - rLocal <= plane11[0].x  && ballPos.x - rLocal >=  plane11[1].x -90 && ballPos.z - rLocal >= plane11[0].z -200 && ballPos.z - rLocal <= plane11[1].z -90 && ballPos.y >= 80 && ballPos.y <= 120)
        gravityLocal.y = 0;

    else
    {
        gravityLocal.z = 0;
        gravityLocal.y = -0.2;
    }

}

// First platform
void moduleOneTest::drawPlatOne()
{
    colour floorOneCol;
    colour deathCol;
    colour sideFloorCol;

    floorOneCol.b = 0; floorOneCol.g = 0.98823; floorOneCol.r = 0.48235;
    sideFloorCol.b = 0.4;  sideFloorCol.g = 0.62352;  sideFloorCol.r = 0.8537;
    deathCol.b = 0.4;  deathCol.g = 0.62352;  deathCol.r = 0.7137;

    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     /*floorOne.setMainAxisValue(-1000);
     floorOne.setAxis2MinVal(plane[0].x-10000);
     floorOne.setAxis2MaxVal(plane[1].x+10000);
     floorOne.setAxis3MinVal(plane[0].z-10000);
     floorOne.setAxis3MaxVal(plane[2].z+1200);
     floorOne.setColour(deathCol);
     floorOne.SetBounceCoefficient(0.7);

     floorOne.display();*/

     floorOne.setMainAxisValue(-100);
     floorOne.setAxis2MinVal(plane[0].x);
     floorOne.setAxis2MaxVal(plane[1].x);
     floorOne.setAxis3MinVal(plane[0].z);
     floorOne.setAxis3MaxVal(plane[2].z);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(plane[0].x);
     sideFloorOne.setAxis2MinVal(plane[0].y - 900);
     sideFloorOne.setAxis2MaxVal(plane[1].y);
     sideFloorOne.setAxis3MinVal(plane[0].z);
     sideFloorOne.setAxis3MaxVal(plane[2].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(plane[1].x);
     sideFloorOne.setAxis2MinVal(plane[0].y - 900);
     sideFloorOne.setAxis2MaxVal(plane[1].y);
     sideFloorOne.setAxis3MinVal(plane[0].z);
     sideFloorOne.setAxis3MaxVal(plane[2].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(plane[0].z);
     frontFloorOne.setAxis2MinVal(plane[0].x);
     frontFloorOne.setAxis2MaxVal(plane[1].x);
     frontFloorOne.setAxis3MinVal(plane[0].y - 900);
     frontFloorOne.setAxis3MaxVal(plane[2].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(plane[2].z);
     frontFloorOne.setAxis2MinVal(plane[0].x);
     frontFloorOne.setAxis2MaxVal(plane[1].x);
     frontFloorOne.setAxis3MinVal(plane[0].y - 900);
     frontFloorOne.setAxis3MaxVal(plane[2].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

}

// Second platform
void moduleOneTest::drawPlatTwo()
{
    colour floorOneCol;
    colour sideFloorCol;

    floorOneCol.b = 0; floorOneCol.g = 0.98823; floorOneCol.r = 0.48235;
    sideFloorCol.b = 0.4;  sideFloorCol.g = 0.62352;  sideFloorCol.r = 0.8537;

    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     floorOne.setMainAxisValue(-100);
     floorOne.setAxis2MinVal(plane[0].x);
     floorOne.setAxis2MaxVal(plane[1].x);
     floorOne.setAxis3MinVal(plane[0].z + 3500);
     floorOne.setAxis3MaxVal(plane[2].z + 1500);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(plane[0].x);
     sideFloorOne.setAxis2MinVal(plane[0].y - 900);
     sideFloorOne.setAxis2MaxVal(plane[1].y);
     sideFloorOne.setAxis3MinVal(plane[0].z + 3500);
     sideFloorOne.setAxis3MaxVal(plane[2].z + 1500);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(plane[1].x);
     sideFloorOne.setAxis2MinVal(plane[0].y - 900);
     sideFloorOne.setAxis2MaxVal(plane[1].y);
     sideFloorOne.setAxis3MinVal(plane[0].z + 3500);
     sideFloorOne.setAxis3MaxVal(plane[2].z + 1500);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(plane[0].z + 3500);
     frontFloorOne.setAxis2MinVal(plane[0].x);
     frontFloorOne.setAxis2MaxVal(plane[1].x);
     frontFloorOne.setAxis3MinVal(plane[0].y - 900);
     frontFloorOne.setAxis3MaxVal(plane[2].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(plane[2].z + 1500);
     frontFloorOne.setAxis2MinVal(plane[0].x);
     frontFloorOne.setAxis2MaxVal(plane[1].x);
     frontFloorOne.setAxis3MinVal(plane[0].y - 900);
     frontFloorOne.setAxis3MaxVal(plane[2].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

}

// Moving Platform 1
void moduleOneTest::drawPlatThree()
{
    colour floorOneCol;
    colour sideFloorCol;

    floorOneCol.b = 0; floorOneCol.g = 0.98823; floorOneCol.r = 0.48235;
    sideFloorCol.b = 0.4;  sideFloorCol.g = 0.62352;  sideFloorCol.r = 0.8537;

    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     floorOne.setMainAxisValue(-100);
     floorOne.setAxis2MinVal(movingBox[0].x);
     floorOne.setAxis2MaxVal(movingBox[1].x);
     floorOne.setAxis3MinVal(movingBox[0].z);
     floorOne.setAxis3MaxVal(movingBox[1].z);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(movingBox[0].x);
     sideFloorOne.setAxis2MinVal(movingBox[0].y);
     sideFloorOne.setAxis2MaxVal(movingBox[1].y - 200);
     sideFloorOne.setAxis3MinVal(movingBox[0].z);
     sideFloorOne.setAxis3MaxVal(movingBox[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(movingBox[1].x);
     sideFloorOne.setAxis2MinVal(movingBox[0].y);
     sideFloorOne.setAxis2MaxVal(movingBox[1].y - 200);
     sideFloorOne.setAxis3MinVal(movingBox[0].z);
     sideFloorOne.setAxis3MaxVal(movingBox[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(movingBox[0].z);
     frontFloorOne.setAxis2MinVal(movingBox[0].x);
     frontFloorOne.setAxis2MaxVal(movingBox[1].x);
     frontFloorOne.setAxis3MinVal(movingBox[0].y);
     frontFloorOne.setAxis3MaxVal(movingBox[1].y - 200);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(movingBox[1].z);
     frontFloorOne.setAxis2MinVal(movingBox[0].x);
     frontFloorOne.setAxis2MaxVal(movingBox[1].x);
     frontFloorOne.setAxis3MinVal(movingBox[0].y - 300);
     frontFloorOne.setAxis3MaxVal(movingBox[1].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

}

// Bonus Platform 1
void moduleOneTest::drawPlatFour()
{
    colour floorOneCol;
    colour sideFloorCol;

    floorOneCol.b = 0; floorOneCol.g = 0.98823; floorOneCol.r = 0.48235;
    sideFloorCol.b = 0.4;  sideFloorCol.g = 0.62352;  sideFloorCol.r = 0.8537;


    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     floorOne.setMainAxisValue(-100);
     floorOne.setAxis2MinVal(plane[0].x+ 2000);
     floorOne.setAxis2MaxVal(plane[1].x+ 2000);
     floorOne.setAxis3MinVal(plane[0].z + 3500);
     floorOne.setAxis3MaxVal(plane[2].z + 1500);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(plane[0].x + 2000);
     sideFloorOne.setAxis2MinVal(plane[0].y - 900);
     sideFloorOne.setAxis2MaxVal(plane[1].y);
     sideFloorOne.setAxis3MinVal(plane[0].z + 3500);
     sideFloorOne.setAxis3MaxVal(plane[2].z + 1500);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(plane[1].x + 2000);
     sideFloorOne.setAxis2MinVal(plane[0].y - 900);
     sideFloorOne.setAxis2MaxVal(plane[1].y);
     sideFloorOne.setAxis3MinVal(plane[0].z + 3500);
     sideFloorOne.setAxis3MaxVal(plane[2].z + 1500);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(plane[0].z + 3500);
     frontFloorOne.setAxis2MinVal(plane[0].x + 2000);
     frontFloorOne.setAxis2MaxVal(plane[1].x + 2000);
     frontFloorOne.setAxis3MinVal(plane[0].y - 900);
     frontFloorOne.setAxis3MaxVal(plane[2].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(plane[2].z + 1500);
     frontFloorOne.setAxis2MinVal(plane[0].x + 2000);
     frontFloorOne.setAxis2MaxVal(plane[1].x + 2000);
     frontFloorOne.setAxis3MinVal(plane[0].y - 900);
     frontFloorOne.setAxis3MaxVal(plane[2].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

    if(collectOne)
    {
        glColor3f(1.0, 1.0, 0.0);

        glPushMatrix ();

        glTranslatef (plane[1].x + 1600, 0 ,plane[1].z + 1350);

        glutSolidSphere(50,50, 50);

        glPopMatrix();

    }

    if (ballPos.x - rLocal >= plane[1].x + 1500 && ballPos.x - rLocal <=  plane[1].x + 1650 && ballPos.z - rLocal >= plane[1].z + 1350 && ballPos.z - rLocal <= plane[1].z + 1500 && ballPos.y - rLocal  >= -50 && ballPos.y - rLocal  <= 50 && collectOne)
    {
        collectOne = false;
        score = score + 500;
    }


}

//Moving platform 2
void moduleOneTest::drawPlatFive()
{
    colour floorOneCol;
    colour sideFloorCol;

    floorOneCol.b = 0; floorOneCol.g = 0.98823; floorOneCol.r = 0.48235;
    sideFloorCol.b = 0.4;  sideFloorCol.g = 0.62352;  sideFloorCol.r = 0.8537;

    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     floorOne.setMainAxisValue(-100);
     floorOne.setAxis2MinVal(movingBox2[0].x);
     floorOne.setAxis2MaxVal(movingBox2[1].x);
     floorOne.setAxis3MinVal(movingBox2[0].z);
     floorOne.setAxis3MaxVal(movingBox2[1].z);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(movingBox2[0].x);
     sideFloorOne.setAxis2MinVal(movingBox2[0].y);
     sideFloorOne.setAxis2MaxVal(movingBox2[1].y - 200);
     sideFloorOne.setAxis3MinVal(movingBox2[0].z);
     sideFloorOne.setAxis3MaxVal(movingBox2[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(movingBox2[1].x);
     sideFloorOne.setAxis2MinVal(movingBox2[0].y);
     sideFloorOne.setAxis2MaxVal(movingBox2[1].y - 200);
     sideFloorOne.setAxis3MinVal(movingBox2[0].z);
     sideFloorOne.setAxis3MaxVal(movingBox2[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(movingBox2[0].z);
     frontFloorOne.setAxis2MinVal(movingBox2[0].x);
     frontFloorOne.setAxis2MaxVal(movingBox2[1].x);
     frontFloorOne.setAxis3MinVal(movingBox2[0].y);
     frontFloorOne.setAxis3MaxVal(movingBox2[1].y - 200);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(movingBox2[1].z);
     frontFloorOne.setAxis2MinVal(movingBox2[0].x);
     frontFloorOne.setAxis2MaxVal(movingBox2[1].x);
     frontFloorOne.setAxis3MinVal(movingBox2[0].y - 300);
     frontFloorOne.setAxis3MaxVal(movingBox2[1].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

}

//falling platform
void moduleOneTest::drawPlatSix()
{
    colour floorOneCol;
    colour sideFloorCol;

    if (colourCounter)
    {
        floorOneCol.b = 0; floorOneCol.g = 0.98823; floorOneCol.r = 0.48235;
    }

    else
    {
        floorOneCol.b = 0; floorOneCol.g = 0.48235; floorOneCol.r = 0.98823;
    }


    sideFloorCol.b = 0.4;  sideFloorCol.g = 0.62352;  sideFloorCol.r = 0.8537;

    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     floorOne.setMainAxisValue(-100);
     floorOne.setAxis2MinVal(dangerBox[0].x);
     floorOne.setAxis2MaxVal(dangerBox[1].x);
     floorOne.setAxis3MinVal(dangerBox[0].z);
     floorOne.setAxis3MaxVal(dangerBox[1].z);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(dangerBox[0].x);
     sideFloorOne.setAxis2MinVal(dangerBox[0].y);
     sideFloorOne.setAxis2MaxVal(dangerBox[1].y - 200);
     sideFloorOne.setAxis3MinVal(dangerBox[0].z);
     sideFloorOne.setAxis3MaxVal(dangerBox[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(dangerBox[1].x);
     sideFloorOne.setAxis2MinVal(dangerBox[0].y);
     sideFloorOne.setAxis2MaxVal(dangerBox[1].y - 200);
     sideFloorOne.setAxis3MinVal(dangerBox[0].z);
     sideFloorOne.setAxis3MaxVal(dangerBox[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(dangerBox[0].z);
     frontFloorOne.setAxis2MinVal(dangerBox[0].x);
     frontFloorOne.setAxis2MaxVal(dangerBox[1].x);
     frontFloorOne.setAxis3MinVal(dangerBox[0].y);
     frontFloorOne.setAxis3MaxVal(dangerBox[1].y - 200);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(dangerBox[1].z);
     frontFloorOne.setAxis2MinVal(dangerBox[0].x);
     frontFloorOne.setAxis2MaxVal(dangerBox[1].x);
     frontFloorOne.setAxis3MinVal(dangerBox[0].y - 300);
     frontFloorOne.setAxis3MaxVal(dangerBox[1].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

}

// platform 3
void moduleOneTest::drawPlatSeven()
{
    colour floorOneCol;
    colour sideFloorCol;

    floorOneCol.b = 0; floorOneCol.g = 0.98823; floorOneCol.r = 0.48235;
    sideFloorCol.b = 0.4;  sideFloorCol.g = 0.62352;  sideFloorCol.r = 0.8537;

    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     floorOne.setMainAxisValue(-100);
     floorOne.setAxis2MinVal(plane6[0].x);
     floorOne.setAxis2MaxVal(plane6[1].x);
     floorOne.setAxis3MinVal(plane6[0].z);
     floorOne.setAxis3MaxVal(plane6[1].z);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(plane6[0].x);
     sideFloorOne.setAxis2MinVal(plane6[0].y);
     sideFloorOne.setAxis2MaxVal(plane6[1].y - 900);
     sideFloorOne.setAxis3MinVal(plane6[0].z);
     sideFloorOne.setAxis3MaxVal(plane6[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(plane6[1].x);
     sideFloorOne.setAxis2MinVal(plane6[0].y);
     sideFloorOne.setAxis2MaxVal(plane6[1].y - 900);
     sideFloorOne.setAxis3MinVal(plane6[0].z);
     sideFloorOne.setAxis3MaxVal(plane6[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(plane6[0].z);
     frontFloorOne.setAxis2MinVal(plane6[0].x);
     frontFloorOne.setAxis2MaxVal(plane6[1].x);
     frontFloorOne.setAxis3MinVal(plane6[0].y);
     frontFloorOne.setAxis3MaxVal(plane6[1].y - 900);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(plane6[1].z);
     frontFloorOne.setAxis2MinVal(plane6[0].x);
     frontFloorOne.setAxis2MaxVal(plane6[1].x);
     frontFloorOne.setAxis3MinVal(plane6[0].y - 900);
     frontFloorOne.setAxis3MaxVal(plane6[1].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

}
// Moving wall
void moduleOneTest::drawPlatEight()
{
    colour floorOneCol;
    colour sideFloorCol;

    floorOneCol.b = 0; floorOneCol.g = 0.48235; floorOneCol.r = 0.98823;

    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     floorOne.setMainAxisValue(movingBox3[0].y);
     floorOne.setAxis2MinVal(movingBox3[0].x);
     floorOne.setAxis2MaxVal(movingBox3[1].x);
     floorOne.setAxis3MinVal(movingBox3[0].z);
     floorOne.setAxis3MaxVal(movingBox3[1].z);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(movingBox3[0].x);
     sideFloorOne.setAxis2MinVal(movingBox3[0].y);
     sideFloorOne.setAxis2MaxVal(movingBox3[1].y);
     sideFloorOne.setAxis3MinVal(movingBox3[0].z);
     sideFloorOne.setAxis3MaxVal(movingBox3[1].z);
     sideFloorOne.setColour(floorOneCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(movingBox3[1].x);
     sideFloorOne.setAxis2MinVal(movingBox3[0].y);
     sideFloorOne.setAxis2MaxVal(movingBox3[1].y);
     sideFloorOne.setAxis3MinVal(movingBox3[0].z);
     sideFloorOne.setAxis3MaxVal(movingBox3[1].z);
     sideFloorOne.setColour(floorOneCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(movingBox3[0].z);
     frontFloorOne.setAxis2MinVal(movingBox3[0].x);
     frontFloorOne.setAxis2MaxVal(movingBox3[1].x);
     frontFloorOne.setAxis3MinVal(movingBox3[0].y);
     frontFloorOne.setAxis3MaxVal(movingBox3[1].y);
     frontFloorOne.setColour(floorOneCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(movingBox3[1].z);
     frontFloorOne.setAxis2MinVal(movingBox3[0].x);
     frontFloorOne.setAxis2MaxVal(movingBox3[1].x);
     frontFloorOne.setAxis3MinVal(movingBox3[0].y);
     frontFloorOne.setAxis3MaxVal(movingBox3[1].y);
     frontFloorOne.setColour(floorOneCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

}

//Last moving platform
void moduleOneTest::drawPlatNine()
{
    colour floorOneCol;
    colour sideFloorCol;

    floorOneCol.b = 0; floorOneCol.g = 0.98823; floorOneCol.r = 0.48235;
    sideFloorCol.b = 0.4;  sideFloorCol.g = 0.62352;  sideFloorCol.r = 0.8537;


    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     floorOne.setMainAxisValue(-100);
     floorOne.setAxis2MinVal(movingBox4[0].x);
     floorOne.setAxis2MaxVal(movingBox4[1].x);
     floorOne.setAxis3MinVal(movingBox4[0].z);
     floorOne.setAxis3MaxVal(movingBox4[1].z);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(movingBox4[0].x);
     sideFloorOne.setAxis2MinVal(movingBox4[0].y);
     sideFloorOne.setAxis2MaxVal(movingBox4[1].y - 200);
     sideFloorOne.setAxis3MinVal(movingBox4[0].z);
     sideFloorOne.setAxis3MaxVal(movingBox4[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(movingBox4[1].x);
     sideFloorOne.setAxis2MinVal(movingBox4[0].y);
     sideFloorOne.setAxis2MaxVal(movingBox4[1].y - 200);
     sideFloorOne.setAxis3MinVal(movingBox4[0].z);
     sideFloorOne.setAxis3MaxVal(movingBox4[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(movingBox4[0].z);
     frontFloorOne.setAxis2MinVal(movingBox4[0].x);
     frontFloorOne.setAxis2MaxVal(movingBox4[1].x);
     frontFloorOne.setAxis3MinVal(movingBox4[0].y);
     frontFloorOne.setAxis3MaxVal(movingBox4[1].y - 200);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(movingBox4[1].z);
     frontFloorOne.setAxis2MinVal(movingBox4[0].x);
     frontFloorOne.setAxis2MaxVal(movingBox4[1].x);
     frontFloorOne.setAxis3MinVal(movingBox4[0].y - 300);
     frontFloorOne.setAxis3MaxVal(movingBox4[1].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

}

//Last platform
void moduleOneTest::drawPlatTen()
{
    colour floorOneCol;
    colour sideFloorCol;

    if (colourCounter)
    {
        floorOneCol.b = 0; floorOneCol.g = 0.98823; floorOneCol.r = 0.48235;
    }

    sideFloorCol.b = 0.4;  sideFloorCol.g = 0.62352;  sideFloorCol.r = 0.8537;

    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     floorOne.setMainAxisValue(-100);
     floorOne.setAxis2MinVal(plane10[0].x);
     floorOne.setAxis2MaxVal(plane10[1].x);
     floorOne.setAxis3MinVal(plane10[0].z);
     floorOne.setAxis3MaxVal(plane10[1].z);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(plane10[0].x);
     sideFloorOne.setAxis2MinVal(plane10[0].y);
     sideFloorOne.setAxis2MaxVal(plane10[1].y - 200);
     sideFloorOne.setAxis3MinVal(plane10[0].z);
     sideFloorOne.setAxis3MaxVal(plane10[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(plane10[1].x);
     sideFloorOne.setAxis2MinVal(plane10[0].y);
     sideFloorOne.setAxis2MaxVal(plane10[1].y - 200);
     sideFloorOne.setAxis3MinVal(plane10[0].z);
     sideFloorOne.setAxis3MaxVal(plane10[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(plane10[0].z);
     frontFloorOne.setAxis2MinVal(plane10[0].x);
     frontFloorOne.setAxis2MaxVal(plane10[1].x);
     frontFloorOne.setAxis3MinVal(plane10[0].y);
     frontFloorOne.setAxis3MaxVal(plane10[1].y - 200);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(plane10[1].z);
     frontFloorOne.setAxis2MinVal(plane10[0].x);
     frontFloorOne.setAxis2MaxVal(plane10[1].x);
     frontFloorOne.setAxis3MinVal(plane10[0].y - 300);
     frontFloorOne.setAxis3MaxVal(plane10[1].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();
}

//Bonus platform 2
void moduleOneTest::drawPlatEleven()
{
    colour floorOneCol;
    colour sideFloorCol;

    floorOneCol.b = 0; floorOneCol.g = 0.98823; floorOneCol.r = 0.48235;
    sideFloorCol.b = 0.4;  sideFloorCol.g = 0.62352;  sideFloorCol.r = 0.8537;

    //AxisAlignedPlane.
    YAlignedPlane floorOne;
    XAlignedPlane sideFloorOne;
    ZAlignedPlane frontFloorOne;
    //(-100, (double)plane[0].x,  (double)plane[1].x, (double)plane[0].z,  (double)plane[2].z, 0.7, floorOneCol);

     floorOne.setMainAxisValue(-100);
     floorOne.setAxis2MinVal(plane11[0].x);
     floorOne.setAxis2MaxVal(plane11[1].x);
     floorOne.setAxis3MinVal(plane11[0].z);
     floorOne.setAxis3MaxVal(plane11[1].z);
     floorOne.setColour(floorOneCol);
     floorOne.SetBounceCoefficient(100);

     floorOne.display();

     sideFloorOne.setMainAxisValue(plane11[0].x);
     sideFloorOne.setAxis2MinVal(plane11[0].y);
     sideFloorOne.setAxis2MaxVal(plane11[1].y - 900);
     sideFloorOne.setAxis3MinVal(plane11[0].z);
     sideFloorOne.setAxis3MaxVal(plane11[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     sideFloorOne.setMainAxisValue(plane11[1].x);
     sideFloorOne.setAxis2MinVal(plane11[0].y);
     sideFloorOne.setAxis2MaxVal(plane11[1].y - 900);
     sideFloorOne.setAxis3MinVal(plane11[0].z);
     sideFloorOne.setAxis3MaxVal(plane11[1].z);
     sideFloorOne.setColour(sideFloorCol);
     sideFloorOne.SetBounceCoefficient(0.7);

     sideFloorOne.display();

     frontFloorOne.setMainAxisValue(plane11[0].z);
     frontFloorOne.setAxis2MinVal(plane11[0].x);
     frontFloorOne.setAxis2MaxVal(plane11[1].x);
     frontFloorOne.setAxis3MinVal(plane11[0].y);
     frontFloorOne.setAxis3MaxVal(plane11[1].y - 900);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     frontFloorOne.setMainAxisValue(plane11[1].z);
     frontFloorOne.setAxis2MinVal(plane11[0].x);
     frontFloorOne.setAxis2MaxVal(plane11[1].x);
     frontFloorOne.setAxis3MinVal(plane11[0].y - 900);
     frontFloorOne.setAxis3MaxVal(plane11[1].y);
     frontFloorOne.setColour(sideFloorCol);
     frontFloorOne.SetBounceCoefficient(0.7);

     frontFloorOne.display();

     if(collectTwo)
    {
        glColor3f(1.0, 1.0, 0.0);

        glPushMatrix ();

        glTranslatef (plane11[0].x - 200, 0 , plane11[0].z + 200);

        glutSolidSphere(50,50, 50);

        glPopMatrix();

    }

    if (ballPos.x - rLocal <= plane[1].x -150 && ballPos.x - rLocal >=  plane[1].x -250 && ballPos.z - rLocal >= plane[1].z + 150 && ballPos.z - rLocal <= plane[1].z + 250 && ballPos.y - rLocal  >= -50 && ballPos.y - rLocal  <= 50 && collectOne)
    {
        collectTwo = false;
        score = score + 500;
    }


}
