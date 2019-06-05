#ifndef AXIS_ALIGNED_PLANE_H
#define AXIS_ALIGNED_PLANE_H

#include "point3D.h"
#include "colour.h"

class AxisAlignedPlane
{
public:
    AxisAlignedPlane() {}

    AxisAlignedPlane(double mainAxisValue, double axis2MinVal, double axis2MaxVal, double axis3MinVal, double axis3MaxVal, double bounceCo, const colour& cl):
    mainAxis(mainAxisValue), axis2Min(axis2MinVal), axis2Max(axis2MaxVal), axis3Min(axis3MinVal), axis3Max(axis3MaxVal), bounceCoefficient(bounceCo), colour(cl) {}

    double getMainAxisValue() {return mainAxis;}

    double getAxis2MinValue() {return axis2Min;}

    double getAxis2MaxValue() {return axis2Max;}

    double getAxis3MinValue() {return axis3Min;}

    double getAxis3MaxValue() {return axis3Max;}

    float getBounceCoefficient() const {return bounceCoefficient;}

    const colour& getColour() const {return colour;}

    void setMainAxisValue(double mainAxisVal) {mainAxis = mainAxisVal;}

    void setAxis2MinVal(double axis2MinVal) {axis2Min = axis2MinVal;}

    void setAxis2MaxVal(double axis2MaxVal) {axis2Max = axis2MaxVal;}

    void setAxis3MinVal(double axis3MinVal) {axis3Min = axis3MinVal;}

    void setAxis3MaxVal(double axis3MaxVal) {axis3Max = axis3MaxVal;}

    ///Can only be 0 or above
    void setBounceCoefficient(float bounceCo);

    void setColour(const colour& cl) {colour = cl;}

    /**
     * calculates what the velocity of the ball should be, based on the ball's current velocity and position
     */
    virtual point3D& getBallVel(const point3D& vel, const point3D& prevPos, float radius) = 0;

    virtual bool collisionDetected(const point3D& vel, const point3D& prevPos, float radius) = 0;

    virtual void display() = 0;

protected:
        ///Value of the plane along its main axis
    double mainAxis;

        ///Minimal value of the plane along its second axis (X is not the main axis, else it is Y)
    double axis2Min;

        ///Maximum value of the plane along its second axis (X if X is not the main axis, else it is Y)
    double axis2Max;

        ///Minimal value of the plane along its third axis (Y if Y is not the main axis, else it is Z)
    double axis3Min;

        ///Maximum value of the plane along its third axis (Y if Y is not the main axis, else it is Z)
    double axis3Max;

        ///The coefficient of the ball's magnitude after collision (how much the ball bounces)
    float bounceCoefficient;

        ///Colour of the plane
    colour colour;
};

#endif
