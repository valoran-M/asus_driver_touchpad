#include <signal.h>
#include <unistd.h>

#include <linux/uinput.h>

#include "event.h"
#include "utility/utility.h"

void remove_key(const devices_info *dev_info, key k) {
    emit(dev_info, EV_KEY, KEY_LEFTSHIFT, 0);
    emit(dev_info, EV_KEY, k.key, 0);
    emit(dev_info, EV_SYN, SYN_REPORT, 0);
}

void emit_key(const devices_info *dev_info, key k) {
    if (k.shifted) {
        emit(dev_info, EV_KEY, KEY_LEFTSHIFT, 1);
    }
    emit(dev_info, EV_KEY, k.key, 1);
    emit(dev_info, EV_SYN, SYN_REPORT, 0);
}

void emit(const devices_info *dev_info, int type, int code, int val) {
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    write(dev_info->file_uinput, &ie, sizeof(ie));
}