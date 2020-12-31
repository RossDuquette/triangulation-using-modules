#ifndef TOPIC_MEASURED_DIST_H_
#define TOPIC_MEASURED_DIST_H_

#include "thread-msg/msg.h"

class MeasuredDistMsg : public Msg {
    public:
        MeasuredDistMsg();

        int& num_beacons;
        float* x_list;
        float* y_list;
        float* radius_list;
};

#endif
