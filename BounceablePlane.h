#ifndef BOUNCEABLE_PLANE
#define BOUNCEABLE_PLANE

#include "structs.h"

class BounceablePlane
{
public:
    /**
     * @param bounds - bounds of the plane
     */
    BounceablePlane(TwoDBounds bounds);

    /**
     * @param bounds - bounds of the plane
     * @param amount - absorbtion factor when the ball bounces off the plane
     */
    BounceablePlane(TwoDBounds bounds, float amount);

    float getAbsorbAmount();

    void setAbsorbAmount(float amount);

private:
        ///absorbtion factor when the ball bounces off the plane
    float absorbAmount;
};

#endif
