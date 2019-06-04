#ifndef Z_ALIGNED_PLANE_H
#define Z_ALIGNED_PLANE_H

#include "AxisAlignedPlane.h"

class ZAlignedPlane: public AxisAlignedPlane
{
public:
    void display();

    point3D getBallVel(const point3D& vel, const point3D& prevPos, float radius, float secondsDelta);
};

#endif
