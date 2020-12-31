#ifndef TOPIC_LOCATION_2D_H_
#define TOPIC_LOCATION_2D_H_

#include "thread-msg/msg.h"

class Location2dMsg : public Msg {
    public:
        Location2dMsg();
        Location2dMsg(float x, float y);

        float& x;
        float& y;
};

#endif
