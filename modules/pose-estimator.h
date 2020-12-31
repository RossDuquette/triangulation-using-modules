#ifndef POSE_ESTIMATOR_H_
#define POSE_ESTIMATOR_H_

#include "msg-types/location-2d.h"
#include "msg-types/measured-dist.h"
#include "thread-msg/module.h"

class PoseEstimator : public Module {
    public:
        PoseEstimator(int id);

        void main() override;

    private:
        void loop();
        void calc_estimate();

        Location2dMsg estimate;
        MeasuredDistMsg measurements;
};

#endif
