#ifndef TOPIC_STRING_H_
#define TOPIC_STRING_H_

#include "thread-msg/msg.h"

class StringMsg : public Msg {
    public:
        StringMsg();
        StringMsg(const char* format, ...);

        char* msg;
};

#endif
