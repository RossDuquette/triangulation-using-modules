#include "topics.h"
#include "triangulation.h"
#include "viewer.h"

Viewer::Viewer(int id) :
    Module(id)
{
}

void Viewer::main()
{
    const int size_pixels = 800;
    const int size_meters = 40;
    const char* name = "Triangulation Kalman Filter";
    gl = std::make_unique<OpenGL>(size_pixels, size_meters, name);
    while (1) {
        loop();
    }
}

void Viewer::loop()
{
    msgr.recv(TOPIC_VEHICLE_LOCATION, &actual_loc);
    msgr.recv(TOPIC_MEASURED_DIST, &beacons);
    msgr.recv(TOPIC_KALMAN_ESTIMATE, &estimate_loc);

    gl->clear();
    draw_beacons();
    draw_estimate();
    draw_vehicle();
    gl->update();
}

void Viewer::draw_beacons()
{
    const float BEACON_SIZE_M = 0.4;
    for (int i = 0; i < beacons.num_beacons; i++) {
        Circle beacon(beacons.x_list[i],
                      beacons.y_list[i],
                      beacons.radius_list[i]);
        gl->draw_square(OpenGL::BLUE, beacon.x, beacon.y, BEACON_SIZE_M);
        gl->draw_circle(OpenGL::RED, beacon.x, beacon.y, beacon.r);
    }
}

void Viewer::draw_estimate()
{
    const float ESTIMATE_RADIUS_M = 0.5;
    gl->draw_circle(OpenGL::GREEN, estimate_loc.x, estimate_loc.y, ESTIMATE_RADIUS_M);
}

void Viewer::draw_vehicle()
{
    const float VEHICLE_SIZE_M = 1;
    gl->draw_square(OpenGL::BLACK, actual_loc.x,  actual_loc.y, VEHICLE_SIZE_M);
}
