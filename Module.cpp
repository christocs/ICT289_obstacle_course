#include "Module.h"

Module::Module(bounds2D newDefaultBounds, point3D newCentre)
{
    default_bounds = newDefaultBounds;
    pos = newCentre;
    setNewBounds();
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
    default_bounds = newDefaultBounds;
    setNewBounds();
}

void Module::setPos(const point3D &newPos)
{
    pos = newPos;
    setNewBounds();
}

void Module::setDefaultBoundsAndPos(const bounds2D &newDefaultBounds, const point3D &newPos)
{
    default_bounds = newDefaultBounds;
    pos = newPos;
    setNewBounds();
}

void Module::setNewBounds()
{
    ///implement
}
