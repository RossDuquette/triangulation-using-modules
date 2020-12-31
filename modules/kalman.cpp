#include <math.h>

#include "kalman.h"
#include "topics.h"

Kalman::Kalman(int id) :
    Module(id),
    estimate(0, 0, 0) // Initial estimate (x, y, theta)
{
}

void Kalman::main()
{
    while (1) {
        loop();
    }
}

void Kalman::loop()
{
    msgr.recv(TOPIC_DRIVE, &motion);
    msgr.recv(TOPIC_VEHICLE_ESTIMATE, &measurement);
    calc_estimate();
    msgr.send(TOPIC_KALMAN_ESTIMATE, &estimate);
}

void Kalman::calc_estimate()
{
    static Pose2dMsg prev_estimate;
    static float state_variance = 1000;
    const float MOTION_VARIANCE = 0.5;
    const float MEASUREMENT_VARIANCE = 10;

    // Prediction
    motion_model();

    // Update
    float K = state_variance / (state_variance + MEASUREMENT_VARIANCE);
    float x_hat = estimate.x + K * (measurement.x - estimate.x);
    float y_hat = estimate.y + K * (measurement.y - estimate.y);
    float theta_hat = copysign(atan2(y_hat - prev_estimate.y,
                                     x_hat - prev_estimate.x), motion.speed);
    state_variance = (1 - K) * state_variance + MOTION_VARIANCE;

    estimate.x = x_hat;
    estimate.y = y_hat;
    estimate.theta = theta_hat;
    prev_estimate.copy_from(estimate);
}

void Kalman::motion_model()
{
    float avg_theta = estimate.theta + motion.theta_dot * motion.dt;
    estimate.theta += motion.theta_dot * motion.dt;
    estimate.theta = limit(estimate.theta, 0, 2 * M_PI);
    estimate.x += motion.speed * motion.dt * cos(avg_theta);
    estimate.y += motion.speed * motion.dt * sin(avg_theta);
}

float Kalman::limit(float input, float lower_bound, float upper_bound)
{
    float range = upper_bound - lower_bound;
    while (input > upper_bound) {
        input -= range;
    }
    while (input < lower_bound) {
        input += range;
    }
    return input;
}
