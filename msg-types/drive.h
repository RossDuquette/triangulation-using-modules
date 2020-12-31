#ifndef TOPIC_DRIVE_H_
#define TOPIC_DRIVE_H_

#include "thread-msg/msg.h"

class DriveMsg : public Msg {
    public:
        DriveMsg();
        DriveMsg(float speed, float theta_dot, float dt);

        float& speed;
        float& theta_dot;
        float& dt;
};

#endif
