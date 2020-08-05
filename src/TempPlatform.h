#ifndef TEMP_PLATFORM_H
#define TEMP_PLATFORM_H

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

#define COLOUR3_R 0.98823
#define COLOUR3_G 0.48235
#define COLOUR3_B 0

#define COLOUR_CHANGE_RATE 100

class TempPlatform: public Object
{
public:
    TempPlatform() = delete;

    TempPlatform(float xMin, float xMax, float y, float zMin, float zMax, float depth, float topBounce, float wallBounce, float ttl);

    void reset();

    void animate(const point3D& currPos, float radius, float t);

    void display();

    point3D getBallVel(const point3D& vel, const point3D& prevPos, float radius);

    bool collisionDetected(const point3D& vel, const point3D& prevPos, float radius);

    bool touchingFloor(const point3D& currPos, float radius);

private:
    XAlignedPlane xPlane1, xPlane2;

    YAlignedPlane yPlane;

    ZAlignedPlane zPlane1, zPlane2;

    bool colour3 = true;

    bool floorTouched = false;

    float timeToLive, initialTimeToLive;

    colour c1, c2, c3;

    float timeSinceLastColour = 0;
};
#endif
