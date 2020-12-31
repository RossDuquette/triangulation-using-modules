#ifndef KALMAN_H_
#define KALMAN_H_

#include "msg-types/drive.h"
#include "msg-types/pose-2d.h"
#include "thread-msg/module.h"

class Kalman : public Module {
    public:
        Kalman(int id);

        void main() override;

    private:
        void loop();
        void calc_estimate();
        void motion_model();
        float limit(float input, float lower_bound, float upper_bound);

        DriveMsg motion;
        Pose2dMsg measurement;
        Pose2dMsg estimate;
};

#endif
