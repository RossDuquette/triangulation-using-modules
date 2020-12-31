#include "drive.h"

DriveMsg::DriveMsg() :
    speed(*(float*) data),
    theta_dot(*(&speed + 1)),
    dt(*(&theta_dot + 1))
{
}

DriveMsg::DriveMsg(float speed, float theta_dot, float dt) :
    DriveMsg()
{
    this->speed = speed;
    this->theta_dot = theta_dot;
    this->dt = dt;
}
