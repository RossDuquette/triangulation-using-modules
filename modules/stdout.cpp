#include <stdio.h>
#include <string.h>

#include "stdout.h"
#include "topics.h"

StdOut::StdOut(int id) :
    Module(id)
{
}

void StdOut::main()
{
    while (1) {
        loop();
    }
}

void StdOut::loop()
{
    msgr.recv(TOPIC_STDOUT, &msg);
    printf("%s\n", msg.msg);
}
