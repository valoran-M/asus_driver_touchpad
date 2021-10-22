#ifndef ASUS_DRIVER_TOUCHPAD_ERROR_H
#define ASUS_DRIVER_TOUCHPAD_ERROR_H

#include <stdio.h>

/**
 *
 * stop get_proc when FAILURE
 *
 * @param char* output
 *
 **/
__attribute__((noreturn))
void error(const char *output);

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
void check_ioctl(int return_code);

#endif //ASUS_DRIVER_TOUCHPAD_ERROR_H
