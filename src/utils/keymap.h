#ifndef ASUS_DRIVER_TOUCHPAD_KEYMAP_H
#define ASUS_DRIVER_TOUCHPAD_KEYMAP_H

#include "defines.h"
#include "utils/utils.h"

void keymap_init(devices_info *dev_info, unsigned short line, unsigned short colonne);

void keymap_free(devices_info *dev_info);

void keymap_set(devices_info *dev_info, unsigned short line, unsigned short colonne, key k);

key keymap_get(devices_info *dev_info, unsigned short line, unsigned short colonne);

#endif //ASUS_DRIVER_TOUCHPAD_KEYMAP_H
