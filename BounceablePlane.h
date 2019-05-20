#ifndef BOUNCEABLE_PLANE
#define BOUNCEABLE_PLANE

#include "bounds2D.h"

class BounceablePlane
{
public:
    /**
     * @param b - bounds of the plane
     */
    BounceablePlane(bounds2D b);

    /**
     * @param b - bounds of the plane
     * @param amount - absorbtion factor when the ball bounces off the plane
     */
    BounceablePlane(bounds2D b, float amount);

    float getAbsorbAmount();

    void setAbsorbAmount(float amount);

    bounds2D getBounds();

    void setBounds(bounds2D b);

    /**
     * returns true if collision detected
     * calculates new velocity of ball if collision happens
     */
    bool calcCollision();

private:
        ///absorbtion factor when the ball bounces off the plane
    float absorbAmount;
};

#endif
