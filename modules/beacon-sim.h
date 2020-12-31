#ifndef BEACON_SIM_H_
#define BEACON_SIM_H_

#include "msg-types/location-2d.h"
#include "msg-types/measured-dist.h"
#include "thread-msg/module.h"

class BeaconSim : public Module {
    public:
        BeaconSim(int id);

        void main() override;

    private:
        void loop();
        float distance_from_beacon(int i);

        Location2dMsg veh_location;
        MeasuredDistMsg beacons;
};

#endif
