#ifndef X_ALIGNED_PLANE_H
#define X_ALIGNED_PLANE_H

#include "AxisAlignedPlane.h"

class XAlignedPlane: public AxisAlignedPlane
{
public:
    void display();

    /** Only approximate collision. Does not test edges. */
    point3D getBallVel(const point3D& vel, const point3D& prevPos, float radius);

    /** Only approximate collision. Does not test edges. */
    bool collisionDetected(const point3D& vel, const point3D& prevPos, float radius);
};

#endif
