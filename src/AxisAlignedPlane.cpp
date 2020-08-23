#include "AxisAlignedPlane.h"
#include <assert.h>

void AxisAlignedPlane::setBounceCoefficient(float bounceCo)
{
    assert(bounceCo >= 0);
    bounceCoefficient = bounceCo;
}
