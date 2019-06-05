#ifndef Y_ALIGNED_PLANE_H
#define Y_ALIGNED_PLANE_H

#include "AxisAlignedPlane.h"

class YAlignedPlane: public AxisAlignedPlane
{
public:
    void display();

    /** Only approximate collision. Does not test edges. Very generous with collisions. */
    point3D getBallVel(const point3D& vel, const point3D& prevPos, float radius);

    /** Only approximate collision. Does not test edges. Very generous with collisions. */
    bool collisionDetected(const point3D& vel, const point3D& prevPos, float radius);

    /** Only approximate collision. Does not test edges. Very generous with collisions. */
    bool touchingFloor(const point3D& vel, const point3D& prevPos, float radius);
};

#endif
