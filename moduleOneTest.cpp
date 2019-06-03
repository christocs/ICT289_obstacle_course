#include "moduleOneTest.h"

moduleOneTest::moduleOneTest()
{

        plane[0].x = -400; plane[0].y = -100; plane[0].z = 1000;
        plane[1].x = 400; plane[1].y = -100; plane[1].z = 3500;
        plane[2].x = 400; plane[2].y = -100; plane[2].z = 3500;

        movingBox[0].x = -400;  movingBox[0].y = -100;  movingBox[0].z = 6500;
        movingBox[1].x = 400;  movingBox[1].y = -200;  movingBox[1].z = 7500;




}

moduleOneTest::~moduleOneTest()
{

}

const point3D* moduleOneTest::getPlaneSize()
{
    return plane;
}


void moduleOneTest::startModuleOne()
{

    animatePlanes();
    detectBallLocation();
    drawPlatOne();
    drawPlatTwo();
    drawPlatThree();
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

        }

        if (movingBox[1].x <= -1500)
            moveLeft = false;

    }

    else
    {
        for (int i = 0; i < 2; i++)
        {
            movingBox[i].x = movingBox[i].x + 5;
        }

        if (movingBox[1].x >= 1500)
            moveLeft = true;

    }

}

void moduleOneTest::detectBallLocation()
{
    /**
    Test functions for if the ball is within the area of the object, and what velocity is placed on it. For example
    if (ballCurrPos.x - radius => movingBox[0].x || ballCurrPos.x - radius <= movingBox[1] etc... )

    Mayvbe the aligned planes do this for me?? I dunno..
    **/
}

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
     floorOne.setAxis3MaxVal(plane[2].z+1000);
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


void moduleOneTest::drawPlatTwo()
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

void moduleOneTest::drawPlatThree()
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
