#include "pose-2d.h"

Pose2dMsg::Pose2dMsg() :
    Location2dMsg(),
    theta(*(&y + 1))
{
}

Pose2dMsg::Pose2dMsg(float x, float y, float theta) :
    Pose2dMsg()
{
    this->x = x;
    this->y = y;
    this->theta = theta;
}
