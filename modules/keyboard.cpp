#include <ncurses.h>

#include "keyboard.h"
#include "msg-types/string.h"
#include "thread-msg/sleep.h"
#include "topics.h"

Keyboard::Keyboard(int id) :
    Module(id)
{
    motion.dt = 0.1;
}

void Keyboard::main()
{
    const float SLEEP_HZ = 10;
    FreqSleeper sleeper(SLEEP_HZ);
    while (1) {
        loop();
        sleeper.sleep();
    }
}

void Keyboard::loop()
{
    //calc_motion(); // Not working
    // Simulate driving in circle instead
    set_speed(3, 0.2);
    msgr.send(TOPIC_DRIVE, &motion);
}

void Keyboard::calc_motion()
{
    const float SPEED_VAL = 3;
    const float THETA_DOT_VAL = 0.2;

    int key = getch();
    switch (key) {
    case 'w':
        set_speed(SPEED_VAL, 0);
        break;
    case 's':
        set_speed(-SPEED_VAL, 0);
        break;
    case 'a':
        set_speed(0, THETA_DOT_VAL);
        break;
    case 'd':
        set_speed(0, -THETA_DOT_VAL);
        break;
    case 'q':
        set_speed(SPEED_VAL, THETA_DOT_VAL);
        break;
    case 'e':
        set_speed(SPEED_VAL, -THETA_DOT_VAL);
        break;
    default:
        set_speed(0, 0);
        break;
    }
}

void Keyboard::set_speed(float speed, float theta_dot)
{
    motion.speed = speed;
    motion.theta_dot = theta_dot;
}
