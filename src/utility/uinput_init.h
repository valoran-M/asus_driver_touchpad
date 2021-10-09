#ifndef UINPUT_H
#define UINPUT_H

#include "utility/utility.h"

#define UINPUT_FILE "/dev/uinput"

/**
 * 
 * setup uinput devices
 * 
 **/
void setup_uinput(devices_info *dev_info);

#endif