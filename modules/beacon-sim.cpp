#include <random>

#include "beacon-sim.h"
#include "topics.h"

BeaconSim::BeaconSim(int id) :
    Module(id)
{
    beacons.num_beacons = 4;
    beacons.x_list[0] = -20; beacons.y_list[0] = -20;
    beacons.x_list[1] = -20; beacons.y_list[1] =  20;
    beacons.x_list[2] =  20; beacons.y_list[2] = -20;
    beacons.x_list[3] =  20; beacons.y_list[3] =  20;
}

void BeaconSim::main()
{
    while (1) {
        loop();
    }
}

void BeaconSim::loop()
{
    msgr.recv(TOPIC_VEHICLE_LOCATION, &veh_location);
    for (int i = 0; i < beacons.num_beacons; i++) {
        distance_from_beacon(i);
    }
    msgr.send(TOPIC_MEASURED_DIST, &beacons);
}

float BeaconSim::distance_from_beacon(int i)
{
    // Std dev of gaussian noise on distance measurements
    const float NOISE_STD_DEV = 3;
    static std::default_random_engine rand;
    static std::normal_distribution<float> norm_dist(0, NOISE_STD_DEV);
    float noise = norm_dist(rand);

    float del_x = beacons.x_list[i] - veh_location.x;
    float del_y = beacons.y_list[i] - veh_location.y;
    beacons.radius_list[i] = sqrt(del_x * del_x + del_y * del_y) + noise;
}
