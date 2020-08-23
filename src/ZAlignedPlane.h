#ifndef Z_ALIGNED_PLANE_H
#define Z_ALIGNED_PLANE_H

#include "AxisAlignedPlane.h"

class ZAlignedPlane: public AxisAlignedPlane
{
public:
    void display();

    /** Only approximate collision. Does not test edges. Just increases size of surface by half of radius for collisions. */
    point3D getBallVel(const point3D& vel, const point3D& prevPos, float radius);

    /** Only approximate collision. Does not test edges. */
    bool collisionDetected(const point3D& vel, const point3D& prevPos, float radius);
};

#endif
