#include <stdarg.h>
#include <stdio.h>

#include "thread-msg/conf.h"
#include "string.h"

StringMsg::StringMsg() :
    msg((char*) data)
{
}

StringMsg::StringMsg(const char* format, ...) :
    StringMsg()
{
    va_list p_list;
    va_start(p_list, format);
    vsnprintf(msg, MAX_MSG_LEN, format, p_list);
}
