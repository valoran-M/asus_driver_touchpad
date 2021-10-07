#include <signal.h>
#include <unistd.h>

#include <linux/uinput.h>

#include "event.h"
#include "utility/utility.h"

void sighandler(int sig)
{
    stop();
}

void remove_key(key k)
{
    emit(EV_KEY, KEY_LEFTSHIFT, 0);
    emit(EV_KEY, k.key, 0);
    emit(EV_SYN, SYN_REPORT, 0);
}

void emit_key(key k)
{
    if (k.shifted)
        emit(EV_KEY, KEY_LEFTSHIFT, 1);
    emit(EV_KEY, k.key, 1);
    emit(EV_SYN, SYN_REPORT, 0);
}

void emit(int type, int code, int val)
{
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    write(info->file_uinput, &ie, sizeof(ie));
}