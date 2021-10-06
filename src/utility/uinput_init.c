#include <string.h>
#include <fcntl.h>

#include <linux/uinput.h>

#include "utility/utility.h"
#include "utility/uinput_init.h"

void setup_uinput(devices_info *info)
{
    struct uinput_setup usetup;

    info->file_uinput = open(UINPUT_FILE, O_WRONLY | O_NONBLOCK);

    ioctl(info->file_uinput, UI_SET_EVBIT, EV_KEY);
    ioctl(info->file_uinput, UI_SET_KEYBIT, KEY_NUMLOCK);
    ioctl(info->file_uinput, UI_SET_KEYBIT, KEY_LEFTSHIFT);
    for (size_t line = 0; line < info->line; line++)
        for (size_t col = 0; col < info->colonne; col++)
            ioctl(info->file_uinput, UI_SET_KEYBIT, info->keys[line][col]);

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234;
    usetup.id.product = 0x5678;
    strcpy(usetup.name, "Asus Touchpad/Numpad driver");

    ioctl(info->file_uinput, UI_DEV_SETUP, &usetup);
    ioctl(info->file_uinput, UI_DEV_CREATE);
}