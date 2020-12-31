#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "msg-types/drive.h"
#include "thread-msg/module.h"

class Keyboard : public Module {
    public:
        Keyboard(int id);

        void main() override;

    private:
        void loop();
        void calc_motion();
        void set_speed(float speed, float theta_dot);

        DriveMsg motion;
};

#endif
