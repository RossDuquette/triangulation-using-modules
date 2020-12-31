#include "location-2d.h"

Location2dMsg::Location2dMsg() :
    x(*(float*) data),
    y(*(&x + 1))
{
}

Location2dMsg::Location2dMsg(float x, float y) :
    Location2dMsg()
{
    this->x = x;
    this->y = y;
}
