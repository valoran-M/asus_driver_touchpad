#include <signal.h>
#include <stdio.h>

#include "event.h"

void sighandler(int sig)
{
    if (sig == SIGINT)
        loop = 0;
}

#include <unistd.h>

#include <linux/uinput.h>

void emit(int file, int type, int code, int val)
{
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    write(file, &ie, sizeof(ie));
    if (type == EV_SYN && code == SYN_REPORT && val == 0)
        emit(file, EV_SYN, SYN_REPORT, 0);
}