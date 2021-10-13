#include <linux/uinput.h>#include "interface.h"


#include "keys_events.h"

static u_int8_t brightness = 0;

void activate_numpad(const devices_info *dev_info)
{
    emit(dev_info, EV_KEY, KEY_NUMLOCK, 1);
    emit(dev_info, EV_SYN, SYN_REPORT, 0);
    brightness = 1;
    i2c_send(dev_info);
    ioctl(dev_info->file_touchpad, EVIOCGRAB, 1);
}

void deactivate_numpad(const devices_info *dev_info)
{
    emit(dev_info, EV_KEY, KEY_NUMLOCK, 0);
    emit(dev_info, EV_SYN, SYN_REPORT, 0);
    brightness = 0;
    i2c_send(dev_info);
    ioctl(dev_info->file_touchpad, EVIOCGRAB, 0);
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

void change_brightness(const devices_info *dev_info)
{
    brightness = (brightness) % 3 + 1;
    i2c_send(dev_info);
}
