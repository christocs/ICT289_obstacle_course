#ifndef MODULEONETEST_H_INCLUDED
#define MODULEONETEST_H_INCLUDED

#include <freeglut.h>




public:
    void startModuleOne()

private:
    void animatePlanes();
    void detectBallLocation();
    void drawPlanes();
    point3D plane[4];
    point3D movingBox[4];


#endif // MODULEONETEST_H_INCLUDED
