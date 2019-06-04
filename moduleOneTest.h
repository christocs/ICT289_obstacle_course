#ifndef MODULEONETEST_H_INCLUDED
#define MODULEONETEST_H_INCLUDED

#include <freeglut.h>
#include "point3D.h"
#include "YAlignedPlane.h"
#include "XAlignedPlane.h"
#include "ZAlignedPlane.h"

class moduleOneTest
{
    public:
        moduleOneTest();
        ~moduleOneTest();
        void startModuleOne();
        const point3D *getPlaneSize();

    private:
        void animatePlanes();
        void detectBallLocation();
        void drawPlatOne();
        void drawPlatTwo();
        void drawPlatThree();
        point3D plane[4];
        point3D movingBox[4];
        bool moveLeft = true;

};

#endif // MODULEONETEST_H_INCLUDED
