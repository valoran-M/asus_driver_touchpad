#include <unistd.h>

#include "init.h"

void stop(devices_info *info)
{
    close(info->file_keyboard);
    close(info->file_touchpad);

    free(info);
}