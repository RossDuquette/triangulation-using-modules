#include <math.h>

#include "topics.h"
#include "vehicle-sim.h"

VehicleSim::VehicleSim(int id) :
    Module(id)
{
}

void VehicleSim::main()
{
    while (1) {
        loop();
    }
}

void VehicleSim::loop()
{
    msgr.recv(TOPIC_DRIVE, &motion);
    float avg_theta = pose.theta + motion.theta_dot * motion.dt;
    pose.theta += motion.theta_dot * motion.dt;
    theta_limit();
    pose.x += motion.speed * motion.dt * cos(avg_theta);
    pose.y += motion.speed * motion.dt * sin(avg_theta);
    msgr.send(TOPIC_VEHICLE_LOCATION, &pose);
}

void VehicleSim::theta_limit()
{
    const float RANGE = 2 * M_PI;
    const float LOWER_LIMIT = 0;
    const float UPPER_LIMIT = LOWER_LIMIT + RANGE;
    while (pose.theta > UPPER_LIMIT) {
        pose.theta -= RANGE;
    }
    while (pose.theta < LOWER_LIMIT) {
        pose.theta += RANGE;
    }
}
