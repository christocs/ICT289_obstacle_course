#ifndef Y_ALIGNED_PLANE_H
#define Y_ALIGNED_PLANE_H

#include "AxisAlignedPlane.h"

class YAlignedPlane: public AxisAlignedPlane
{
public:
    void display();

    point3D getBallVel(const point3D& vel, const point3D& prevPos, float radius, float secondsDelta);
};

#endif
