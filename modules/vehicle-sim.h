#ifndef VEHICLE_SIM_H_
#define VEHICLE_SIM_H_

#include "msg-types/drive.h"
#include "msg-types/pose-2d.h"
#include "thread-msg/module.h"

class VehicleSim : public Module {
    public:
        VehicleSim(int id);

        void main() override;

    private:
        void loop();
        void theta_limit();

        DriveMsg motion;
        Pose2dMsg pose;
};

#endif
