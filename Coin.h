#ifndef COIN_H
#define COIN_H

#include "point3D.h"
#include "Object.h"

#define COLOUR_R 1
#define COLOUR_G 1
#define COLOUR_B 0

class Coin: public Object
{
public:
    Coin() = delete;

    Coin(float x, float y, float z, float radius);

    void animate(const point3D& ballPos, float radius, float t);

    void display();

    point3D getBallVel(const point3D& vel, const point3D& prevPos, float rad);

    bool collisionDetected(const point3D& vel, const point3D& prevPos, float radius) {return false;}

    bool touchingFloor(const point3D& currPos, float radius) {return false;}

    void reset();

private:
    point3D pos;

    float rad;

    bool collected = false;
};
#endif
