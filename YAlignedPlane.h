#ifndef Y_ALIGNED_PLANE_H
#define Y_ALIGNED_PLANE_H

#include "AxisAlignedPlane.h"

class YAlignedPlane: public AxisAlignedPlane
{
public:
    void display();

    const point3D& getBallVel(const point3D& vel, const point3D& prevPos, float secondsDelta);
};

#endif
