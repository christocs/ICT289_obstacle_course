#ifndef Module_H
#define Module_H

#include "bounds2D.h"
#include "point3D.h"

/**
 * Abstract class for what a module should have at minimum
 */
class Module   // abstract because of pure virtual methods
{
public:
    /** Sets size of bounds
     */
    Module(bounds2D newDefaultBounds, point3D newCentre);

    /** Method should be triggered when the ball enters the module
     *  Can be empty
     */
    virtual void onBallEnter() = 0;

    /** Method should be triggered when the ball enters the exits
     *  Can be empty
     */
    virtual void onBallExit() = 0;

    /** Method should be triggered every tick to display animations
     *  Can be empty
     */
    virtual void animate() = 0;

    /** Method should be triggered every tick to the ball is in the module
     */
    virtual void onTickInModule() = 0;

    /** Method should be triggered everytime the display() function in a freeglut program is called
     */
    virtual void display() = 0;

    const point3D& getPos() const;

    const bounds2D& getBounds() const;

    const bounds2D& getDefaultBounds() const;

    void setDefaultBounds(const bounds2D &newDefaultBounds);

    void setPos(const point3D &newPos);

    void setDefaultBoundsAndPos(const bounds2D &newDefaultBounds, const point3D &newPos);

protected:
    /** Sets bounds of the module according to the centre of the module and the default bounds
     */
    void setNewBounds();

    /** Defining bounds for the module, assuming the centre is the origin
     *  note that it doesn't take into account height, so modules can't be stacked
     */
    bounds2D default_bounds;

    /** The bounds for the module based on the pos
     *  note that it doesn't take into account height, so modules can't be stacked
     */
    bounds2D bounds;

    /** The position of the module's centre
     */
    point3D pos;
};

#endif
