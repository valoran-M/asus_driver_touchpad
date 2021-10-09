#include <string.h>
#include <stdlib.h>

#include <fcntl.h>

#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/i2c-dev.h>

#ifndef I2C_M_RD
#include <linux/i2c.h>
#endif

#include "event.h"
#include "material.h"

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

void change_brightness(const devices_info *dev_info)
{
    brightness = (brightness) % 3 + 1;
    i2c_send(dev_info);
}

void i2c_send(const devices_info *dev_info)
{
    buf[11] = bright[brightness];

    struct i2c_msg message[] = {
        {
            .addr = (__u16)0x15,
            .buf = buf,
            .len = (__u16)13,
        },
    };

    struct i2c_rdwr_ioctl_data payload =
        {
            .msgs = message,
            .nmsgs = sizeof(message) / sizeof(message[0]),
        };

    ioctl(dev_info->i2c, I2C_RDWR, &payload);
}