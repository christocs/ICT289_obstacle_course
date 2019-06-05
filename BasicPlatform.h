#ifndef BASIC_PLATFORM_H
#define BASIC_PLATFORM_H

#include "Object.h"

#include "XAlignedPlane.h"
#include "YAlignedPlane.h"
#include "ZAlignedPlane.h"

#define COLOUR1_R 0.48235
#define COLOUR1_G 0.98823
#define COLOUR1_B 0

#define COLOUR2_R 0.8537
#define COLOUR2_G 0.62352
#define COLOUR2_B 0.4

class BasicPlatform: public Object
{
public:
    BasicPlatform() = delete;

    BasicPlatform(float xMin, float xMax, float y, float zMin, float zMax, float depth, float topBounce, float wallBounce);

    void display();

    point3D getBallVel(const point3D& vel, const point3D& prevPos, float radius);

    bool collisionDetected(const point3D& vel, const point3D& prevPos, float radius);

    bool touchingFloor(const point3D& vel, const point3D& prevPos, float radius);

private:
    XAlignedPlane xPlane1, xPlane2;

    YAlignedPlane yPlane;

    ZAlignedPlane zPlane1, zPlane2;
};
#endif
