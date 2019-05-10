#ifndef BOUNCEABLE_PLANE
#define BOUNCEABLE_PLANE

#include "bounds2D.h"

class BounceablePlane
{
public:
    /**
     * @param bounds - bounds of the plane
     */
    BounceablePlane(bounds2D bounds);

    /**
     * @param bounds - bounds of the plane
     * @param amount - absorbtion factor when the ball bounces off the plane
     */
    BounceablePlane(bounds2D bounds, float amount);

    float getAbsorbAmount();

    void setAbsorbAmount(float amount);

private:
        ///absorbtion factor when the ball bounces off the plane
    float absorbAmount;
};

#endif
