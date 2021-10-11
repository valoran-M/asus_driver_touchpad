#include <unistd.h>

#include <linux/input.h>
#include <linux/uinput.h>

#include "utility/utility.h"

void max_min(devices_info *dev_info)
{
    int abs[6] = {0}; // TO CHECK : 6 int isn't too wide ?

    ioctl(dev_info->file_touchpad, EVIOCGABS(ABS_X), abs);
    dev_info->x.min = abs[1];
    dev_info->x.max = abs[2];

    ioctl(dev_info->file_touchpad, EVIOCGABS(ABS_Y), abs);
    dev_info->y.min = abs[1];
    dev_info->y.max = abs[2];
}

void stop(devices_info *dev_info)
{
    close(dev_info->file_touchpad);
    if (dev_info->i2c != -1) {
        close(dev_info->i2c);
    }

    ioctl(dev_info->file_uinput, UI_DEV_DESTROY);
    close(dev_info->file_uinput);

    for (size_t i = 0; i < dev_info->line; i++) {
        free(dev_info->keys[i]);
    }
    free(dev_info->keys);

    exit(EXIT_SUCCESS);
}