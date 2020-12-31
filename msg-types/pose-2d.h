#ifndef TOPIC_POSE_2D_H_
#define TOPIC_POSE_2D_H_

#include "location-2d.h"

class Pose2dMsg : public Location2dMsg {
    public:
        Pose2dMsg();
        Pose2dMsg(float x, float y, float theta);

        float& theta;
};

#endif
