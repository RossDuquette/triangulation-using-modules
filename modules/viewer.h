#ifndef VIEWER_H_
#define VIEWER_H_

#include <memory>

#include "msg-types/location-2d.h"
#include "msg-types/measured-dist.h"
#include "msg-types/pose-2d.h"
#include "open-gl.h"
#include "thread-msg/module.h"

class Viewer : public Module {
    public:
        Viewer(int id);

        void main() override;

    private:
        void loop();
        void draw_beacons();
        void draw_estimate();
        void draw_vehicle();

        std::unique_ptr<OpenGL> gl;
        MeasuredDistMsg beacons;
        Location2dMsg estimate_loc;
        Pose2dMsg actual_loc;
};

#endif
