#ifndef X_ALIGNED_PLANE_H
#define X_ALIGNED_PLANE_H

#include "AxisAlignedPlane.h"

class XAlignedPlane: public AxisAlignedPlane
{
public:
    void display();

    point3D getBallVel(const point3D& vel, const point3D& prevPos, float radius, float secondsDelta);
};

#endif
