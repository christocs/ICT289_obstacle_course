#ifndef Y_MOVING_PLATFORM_H
#define Y_MOVING_PLATFORM_H

#include "Object.h"

#include "XAlignedPlane.h"
#include "YAlignedPlane.h"
#include "ZAlignedPlane.h"

#define COLOUR_R 0.98823
#define COLOUR_G 0.48235
#define COLOUR_B 0

class YMovingPlatform: public Object
{
public:
    YMovingPlatform() = delete;

    YMovingPlatform(float xMin, float xMax, float y, float zMin, float zMax, float depth, float topBounce, float wallBounce, float dist, float s, bool upStart);

    void animate(const point3D& currPos, float radius, float t);

    void reset();

    void display();

    point3D getBallVel(const point3D& vel, const point3D& prevPos, float radius);

    bool collisionDetected(const point3D& vel, const point3D& prevPos, float radius);

    bool touchingFloor(const point3D& currPos, float radius);

private:
    XAlignedPlane xPlane1, xPlane2;

    YAlignedPlane yPlane;

    ZAlignedPlane zPlane1, zPlane2;

    float yMinBegin, yMaxBegin;

    bool beginUp;

    float distance, speed;

    //Movement direction of platform
    bool up;
};
#endif
