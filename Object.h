#ifndef Object_H
#define Object_H

class Object
{
public:
    Object();

    void animate();

    void display();

    point3D& getBallVel(const point3D& vel, const point3D& prevPos, float radius, float secondsDelta);

    bool collisionDetected(const point3D& vel, const point3D& prevPos, float radius, float secondsDelta);
};
#endif
