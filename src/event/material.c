#include <string.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/i2c-dev.h>

#include "event.h"
#include "material.h"

void activate_numpad()
{
    emit(EV_KEY, KEY_NUMLOCK, 1);
    emit(EV_SYN, SYN_REPORT, 0);
    brightness = 1;
    i2c_send();
    ioctl(info->file_touchpad, EVIOCGRAB, 1);
}

void desactivate_numpad()
{
    emit(EV_KEY, KEY_NUMLOCK, 0);
    emit(EV_SYN, SYN_REPORT, 0);
    brightness = 0;
    i2c_send();
    ioctl(info->file_touchpad, EVIOCGRAB, 0);
}

void change_brightness()
{
    brightness = (brightness) % 3 + 1;
    i2c_send();
}

void i2c_send()
{
    char command[100] = "i2ctransfer -f -y ";
    char adr[3];
    sprintf(adr, "%d", info->i2c);
    strcat(command, adr);
    strcat(command, " w13@0x15 0x05 0x00 0x3d 0x03 0x06 0x00 0x07 0x00 0x0d 0x14 0x03 ");
    strcat(command, bright[brightness]);
    strcat(command, " 0xad");
    system(command);
}