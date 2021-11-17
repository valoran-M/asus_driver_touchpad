#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/uinput.h>

__attribute__((noreturn)) void error(const char *output, devices_info *dev_info)
{
    fprintf(stderr, "[ERROR] : %s", output);
    cleanup(dev_info);
    exit(EXIT_FAILURE);
}

void warning(const char *output)
{
    fprintf(stderr, "[WARNING] : %s", output);
}

void check_ioctl(int return_code, devices_info *dev_info)
{
    if (return_code == -1)
    {
        error("ioctl() call failed.", dev_info);
    }
}

void cleanup(devices_info *dev_info)
{
    if (dev_info->file_touchpad != -1)
    {
        close(dev_info->file_touchpad);
    }
    if (dev_info->file_i2c != -1)
    {
        close(dev_info->file_i2c);
    }
    if (dev_info->file_uinput != -1)
    {
        ioctl(dev_info->file_uinput, UI_DEV_DESTROY);
        close(dev_info->file_uinput);
    }
    if (dev_info->mapping.keys != NULL)
    {
        keymap_free(dev_info);
    }
}
