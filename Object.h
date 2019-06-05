#ifndef Object_H
#define Object_H

class Object
{
public:
    void animate() {}

    virtual void display() = 0;

    virtual point3D& getBallVel(const point3D& vel, const point3D& prevPos, float radius) = 0;

    virtual bool collisionDetected(const point3D& vel, const point3D& prevPos, float radius) = 0;

    void reset() {}
};
#endif
