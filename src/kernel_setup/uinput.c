#include <string.h>
#include <fcntl.h>

#include <linux/uinput.h>

#include "uinput.h"

void setup_uinput(devices_info *dev_info)
{
    struct uinput_setup usetup;

    dev_info->file_uinput = open(UINPUT_FILE, O_WRONLY | O_NONBLOCK);

    ioctl(dev_info->file_uinput, UI_SET_EVBIT, EV_KEY);
    ioctl(dev_info->file_uinput, UI_SET_KEYBIT, KEY_NUMLOCK);
    ioctl(dev_info->file_uinput, UI_SET_KEYBIT, KEY_LEFTSHIFT);

    for (size_t line = 0; line < dev_info->line; line++)
        for (size_t col = 0; col < dev_info->colonne; col++)
            ioctl(dev_info->file_uinput, UI_SET_KEYBIT, dev_info->keys[line][col].key);

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_PCI;
    usetup.id.vendor = 0x1234;
    usetup.id.product = 0x5678;
    strcpy(usetup.name, "Asus Touchpad/Numpad driver");

    ioctl(dev_info->file_uinput, UI_DEV_SETUP, &usetup);
    ioctl(dev_info->file_uinput, UI_DEV_CREATE);
}