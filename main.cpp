#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

#include "modules.h"
#include "stdout.h"
#include "topics.h"

#include "beacon-sim.h"
#include "kalman.h"
#include "keyboard.h"
#include "pose-estimator.h"
#include "vehicle-sim.h"
#include "viewer.h"

static Module* modules[NUM_MODULES];
static int num_modules = 0;

static void signal_handler(int signum)
{
    for (int mod = 0; mod < num_modules; mod++) {
        delete modules[mod];
    }
    exit(signum);
}

int main()
{
    static_assert(NUM_MODULES <= MAX_NUM_MODULES);
    static_assert(NUM_TOPICS <= MAX_NUM_TOPICS);

    signal(SIGINT, signal_handler);

    modules[num_modules++] = new StdOut(MODULE_STDOUT);

    modules[num_modules++] = new BeaconSim(MODULE_BEACON_SIM);
    modules[num_modules++] = new Kalman(MODULE_KALMAN);
    modules[num_modules++] = new Keyboard(MODULE_KEYBOARD);
    modules[num_modules++] = new PoseEstimator(MODULE_POSE_ESTIMATOR);
    modules[num_modules++] = new VehicleSim(MODULE_VEHICLE_SIM);
    modules[num_modules++] = new Viewer(MODULE_VIEWER);

    for (int mod = 0; mod < num_modules; mod++) {
        modules[mod]->start();
    }

    pthread_exit(NULL);

    return 0;
}
