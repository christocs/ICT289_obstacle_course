#include <moduleOneTest.h>


moduleOneTest()
{
 /** Set the starting values of all the objects in the module **/
}

~moduleOneTest()
{

}

point3 moduleOneTest::getPlaneSize()
{
    return plane[4];
}


void moduleOneTest::startModuleOne()
{
    animatePlanes();
    detectBallLocation();
    drawPlanes();
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
}

void moduleOneTest::detectBallLocation()
{
    /**
    Test functions for if the ball is within the area of the object, and what velocity is placed on it. For example
    if (ballCurrPos.x - radius => movingBox[0].x || ballCurrPos.x - radius <= movingBox[1] etc... )

    Mayvbe the aligned planes do this for me?? I dunno..
    **/
}

void moduleOneTest:: drawPlanes()
{
     /**
     Send points for objects to the appropriate x/y/z aligned plane For example
        XAlignedPlane(plane[4]);
     to create the plane
     **/
}
