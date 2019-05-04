#ifndef Module_H
#define Module_H

//This is bad design, move structs in headers to separate files
//Defines a 3d vector
struct Vector {
    bool x;
    bool y;
    bool z;
};

//Defines a 3d point
struct point3D {
    float x;
    float y;
    float z;
};

//2D bounds for something
struct TwoDBounds {
    point3D min_b;
    point3D max_b;
};

/**
 * Abstract class for what a module should have at minimum
 * @todo separate implementation from header
 */
class Module { // abstract because of pure virtual methods
public:
    /** Sets size of bounds and centre
     */
    Module(TwoDBounds newDefaultBounds, point3D newCentre);

    ~Module();

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

    const TwoDBounds& getBounds() const;

    const TwoDBounds& getDefaultBounds() const;

    void setDefaultBounds(const TwoDBounds &newDefaultBounds);

    void setPos(const point3D &newPos);

    void setDefaultBoundsAndPos(const TwoDBounds &newDefaultBounds, const point3D &newPos);

protected:
    /** Sets bounds of the module according to the centre of the module and the default bounds
     *  @todo: implement
     */
    void setNewBounds();

    /** Defining bounds for the module, assuming the centre is the origin
     *  note that it doesn't take into account height, so modules can't be stacked
     */
    TwoDBounds default_bounds;

    /** The bounds for the module based on the pos
     *  note that it doesn't take into account height, so modules can't be stacked
     */
    TwoDBounds bounds;

    /** The position of the module's centre
     */
    point3D pos;
};

#endif
