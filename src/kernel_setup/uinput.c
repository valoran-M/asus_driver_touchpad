#include <string.h>
#include <fcntl.h>

#include <linux/uinput.h>

#include "uinput.h"

void setup_uinput(devices_info *dev_info)
{
    struct uinput_setup u_setup;

    dev_info->file_uinput = open(UINPUT_FILE, O_WRONLY | O_NONBLOCK);

    if (dev_info->file_uinput == -1)
        error("Failed to open uinput file.", dev_info);

    check_ioctl(ioctl(dev_info->file_uinput, UI_SET_EVBIT, EV_KEY), dev_info);
    check_ioctl(ioctl(dev_info->file_uinput, UI_SET_KEYBIT, KEY_NUMLOCK), dev_info);
    check_ioctl(ioctl(dev_info->file_uinput, UI_SET_KEYBIT, KEY_LEFTSHIFT), dev_info);

    for (unsigned short line = 0; line < dev_info->mapping.line; line++)
        for (unsigned short col = 0; col < dev_info->mapping.colonne; col++)
            check_ioctl(ioctl(dev_info->file_uinput, UI_SET_KEYBIT,
                              keymap_get(dev_info, line, col).key),
                        dev_info);

    memset(&u_setup, 0x00, sizeof(u_setup));
    u_setup.id.bustype = BUS_PCI;
    u_setup.id.vendor = 0xa74d;
    u_setup.id.product = 0xcc59;
    strcpy(u_setup.name, "Asus Touchpad/Numpad driver");

    check_ioctl(ioctl(dev_info->file_uinput, UI_DEV_SETUP, &u_setup), dev_info);
    check_ioctl(ioctl(dev_info->file_uinput, UI_DEV_CREATE), dev_info);
}