#include "Module.h"

Module::Module(const bounds2D& newDefaultBounds, const point3D& newCentre)
{
    pos = newCentre;
    setDefaultBounds(newDefaultBounds);
}

const point3D& Module::getPos() const
{
    return pos;
}

const bounds2D& Module::getBounds() const
{
    return bounds;
}

const bounds2D& Module::getDefaultBounds() const
{
    return default_bounds;
}

void Module::setDefaultBounds(const bounds2D &newDefaultBounds)
{
    default_bounds[0] = newDefaultBounds[0];
    default_bounds[1] = newDefaultBounds[1];
    setNewBounds();
}

void Module::setPos(const point3D &newPos)
{
    pos = newPos;
    setNewBounds();
}

void Module::setDefaultBoundsAndPos(const bounds2D &newDefaultBounds, const point3D &newPos)
{
    pos = newPos;
    setDefaultBounds(newDefaultBounds);
}

void Module::setNewBounds()
{
    ///implement
}
