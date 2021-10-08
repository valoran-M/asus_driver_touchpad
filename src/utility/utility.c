#include <unistd.h>

#include <linux/input.h>
#include <linux/uinput.h>

#include "utility/utility.h"

void max_min()
{
    int abs[6] = {0};

    ioctl(info->file_touchpad, EVIOCGABS(ABS_X), abs);
    info->x.min = abs[1];
    info->x.max = abs[2];

    ioctl(info->file_touchpad, EVIOCGABS(ABS_Y), abs);
    info->y.min = abs[1];
    info->y.max = abs[2];
}

void stop()
{
    close(info->file_keyboard);
    close(info->file_touchpad);
    close(info->i2c);

    ioctl(info->file_uinput, UI_DEV_DESTROY);

    close(info->file_uinput);

    for (size_t i = 0; i < info->line; i++)
        free(info->keys[i]);
    free(info->keys);

    free(info);

    exit(EXIT_SUCCESS);
}