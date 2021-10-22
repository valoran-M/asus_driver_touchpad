#ifndef ASUS_DRIVER_TOUCHPAD_UTILS_H
#define ASUS_DRIVER_TOUCHPAD_UTILS_H

#include <stdio.h>

#include "defines.h"
#include "keymap.h"

/**
 *
 * stop get_proc when FAILURE
 *
 * @param char* output
 *
 **/
__attribute__((noreturn))
void error(const char *output, devices_info *dev_info);

/**
 *
 * Print warning message
 *
 * @param char* output
 *
 **/
void warning(const char *output);

/**
 *
 * Check ioctl return code
 *
 * @param int code
 *
 **/
void check_ioctl(int return_code, devices_info *dev_info);

void cleanup(devices_info *dev_info);

#endif //ASUS_DRIVER_TOUCHPAD_UTILS_H
