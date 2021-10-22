#ifndef INTERFACE_H
#define INTERFACE_H

#include "defines.h"
#include "utils/utils.h"

/**
 * 
 * send buf with brigthness on file_i2c file
 * 
 **/
void i2c_send(devices_info *dev_info);

/**
 * emit a events
 *
 * @param int events type
 * @param int events code
 * @param int events val
 *
 **/
void emit(devices_info *dev_info, unsigned short type, unsigned short code, int val);

#endif // INTERFACE_H