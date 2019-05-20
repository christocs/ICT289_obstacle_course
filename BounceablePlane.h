#ifndef BOUNCEABLE_PLANE
#define BOUNCEABLE_PLANE

#include "point3D.h"
#include "colour.h"
#include "rectangleCorners.h"

class BounceablePlane
{
public:
    /**
     * @param c - corners of the plane
     * @param amount - absorbtion factor when the ball bounces off the plane
     */
    BounceablePlane(const rectangleCorners& c, float amount, const colour& cl);

    float getAbsorbAmount() const;

    void setAbsorbAmount(float amount);

    const colour& getColour() const;

    void setColour(const colour& cl);

    const rectangleCorners& getCorners() const;

    /**
     * Set the corners of the plane and change the normal vector to match the bounds
     */
    void setCorners(const rectangleCorners& c);

    /**
     * calculates what the velocity of the ball should be, based on the ball's current velocity and position
     */
    const point3D& calcBallVel(const point3D& vel, const point3D& prevPos, float secondsDelta);

    void display();

private:
        ///absorbtion factor when the ball bounces off the plane
    float absorbAmount;

    rectangleCorners corners;

    point3D centre;

        ///Normal vector of the plane
    point3D normal;

    colour colour;

    /**
     * Set the normal of the plane based on the plane corners
     */
    void setNormalVector(const rectangleCorners& c);

    /**
     * Set the centre of the plane based on the plane corners
     */
    void setCentre(const rectangleCorners& c);

    double calcMagnitude(const point3D& v);
};

#endif
