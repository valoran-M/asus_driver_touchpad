#include <unistd.h>

#include <linux/input.h>
#include <linux/uinput.h>

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

    ioctl(info->file_uinput, UI_DEV_DESTROY);

    close(info->file_uinput);

    for (size_t i = 0; i < info->line; i++)
        free(info->keys[i]);
    free(info->keys);

    free(info);
}