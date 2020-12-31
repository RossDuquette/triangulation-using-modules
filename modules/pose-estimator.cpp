#include "pose-estimator.h"
#include "topics.h"
#include "triangulation.h"

PoseEstimator::PoseEstimator(int id) :
    Module(id)
{
}

void PoseEstimator::main()
{
    while (1) {
        loop();
    }
}

void PoseEstimator::loop()
{
    msgr.recv(TOPIC_MEASURED_DIST, &measurements);
    calc_estimate();
    msgr.send(TOPIC_VEHICLE_ESTIMATE, &estimate);
}

void PoseEstimator::calc_estimate()
{
    estimate.x = 0;
    estimate.y = 0;
    float num_estimates = 0;
    float* x =  measurements.x_list;
    float* y =  measurements.y_list;
    float* r =  measurements.radius_list;
    int len = measurements.num_beacons;
    for (int i = 0; i < len; i++) {
        Circle circle1(x[i], y[i], r[i]);
        for (int j = i + 1; j < len; j++) {
            Circle circle2(x[j], y[j], r[j]);
            for (int k = j + 1; k < len; k++) {
                Circle circle3(x[k], y[k], r[k]);
                Point pos = triangulation(circle1, circle2, circle3);
                estimate.x += pos.x;
                estimate.y += pos.y;
                num_estimates += 1;
            }
        }
    }
    estimate.x *= 1.0 / num_estimates;
    estimate.y *= 1.0 / num_estimates;
}
