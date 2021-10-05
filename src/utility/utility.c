#include <unistd.h>

#include <linux/input.h>

#include "utility.h"

void max_min(devices_info *info)
{
    int abs[6] = {0};
    ioctl(info->file_touchpad, EVIOCGABS(ABS_X), abs);
    info->x.min = abs[1];
    info->x.max = abs[2];

    ioctl(info->file_touchpad, EVIOCGABS(ABS_Y), abs);
    info->y.min = abs[1];
    info->y.max = abs[2];

    printf("\nx : \n  min: %d\n  max: %d\n", info->x.min, info->x.max);
    printf("\ny : \n  min: %d\n  max: %d\n", info->y.min, info->y.max);
}

void stop(devices_info *info)
{
    close(info->file_keyboard);
    close(info->file_touchpad);

    free(info);
}