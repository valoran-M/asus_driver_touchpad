#ifndef INTERFACE_H
#define INTERFACE_H

#include "defines.h"
#include "error.h"

/**
 * 
 * send buf with brigthness on i2c file
 * 
 **/
void i2c_send(const devices_info *dev_info);

/**
 * emit a events
 *
 * @param int events type
 * @param int events code
 * @param int events val
 *
 **/
void emit(const devices_info *dev_info, unsigned short type, unsigned short code, int val);

#endif // INTERFACE_H