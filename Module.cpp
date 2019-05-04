#include "Module.h"

Module::Module(TwoDBounds newDefaultBounds, point3D newCentre) {
    default_bounds = newDefaultBounds;
    pos = newCentre;
    setNewBounds();
}

Module::~Module() {

}

const point3D& Module::getPos() const {
    return pos;
}

const TwoDBounds& Module::getBounds() const {
    return bounds;
}

const TwoDBounds& Module::getDefaultBounds() const {
    return default_bounds;
}

void Module::setDefaultBounds(const TwoDBounds &newDefaultBounds) {
    default_bounds = newDefaultBounds;
    setNewBounds();
}

void Module::setPos(const point3D &newPos) {
    pos = newPos;
    setNewBounds();
}

void Module::setDefaultBoundsAndPos(const TwoDBounds &newDefaultBounds, const point3D &newPos) {
    default_bounds = newDefaultBounds;
    pos = newPos;
    setNewBounds();
}

/** Sets bounds of the module according to the centre of the module and the default bounds
 *  @todo: implement
 */
void Module::setNewBounds() {

}
