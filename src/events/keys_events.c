#include <linux/uinput.h>

#include "keys_events.h"

void activate_numpad(devices_info *dev_info)
{
    emit(dev_info, EV_KEY, KEY_NUMLOCK, 1);
    emit(dev_info, EV_SYN, SYN_REPORT, 0);
    dev_info->brightness = 1;
    i2c_send(dev_info);
    check_ioctl(ioctl(dev_info->file_touchpad, EVIOCGRAB, 1));
}

void deactivate_numpad(devices_info *dev_info)
{
    emit(dev_info, EV_KEY, KEY_NUMLOCK, 0);
    emit(dev_info, EV_SYN, SYN_REPORT, 0);
    dev_info->brightness = 0;
    i2c_send(dev_info);
    check_ioctl(ioctl(dev_info->file_touchpad, EVIOCGRAB, 0));
}

void release_key(const devices_info *dev_info, key k)
{
    emit(dev_info, EV_KEY, KEY_LEFTSHIFT, 0);
    emit(dev_info, EV_KEY, k.key, 0);
    emit(dev_info, EV_SYN, SYN_REPORT, 0);
}

void press_key(const devices_info *dev_info, key k)
{
    if (k.shifted) {
        emit(dev_info, EV_KEY, KEY_LEFTSHIFT, 1);
    }
    emit(dev_info, EV_KEY, k.key, 1);
    emit(dev_info, EV_SYN, SYN_REPORT, 0);
}

void change_brightness(devices_info *dev_info)
{
    dev_info->brightness = dev_info->brightness % 3 + 1;
    i2c_send(dev_info);
}
