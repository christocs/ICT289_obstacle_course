#ifndef GLOBALS_H
#define GLOBALS_H

//Defines a 3d vector
struct Vector
{
    bool x;
    bool y;
    bool z;
};

//Defines a 3d point
struct point3D
{
    float x;
    float y;
    float z;
};

//2D bounds for something
struct TwoDBounds
{
    point3D min_b;
    point3D max_b;
};

struct direction
{
    bool posX;
    bool negX;
    bool posZ;
    bool negZ;
};

#endif
