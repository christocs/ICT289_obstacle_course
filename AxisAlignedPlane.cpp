#include "AxisAlignedPlane.h"
#include <assert.h>

void AxisAlignedPlane::SetBounceCoefficient(float bounceCo)
{
    assert(bounceCo >= 0);
    bounceCoefficient = bounceCo;
}
