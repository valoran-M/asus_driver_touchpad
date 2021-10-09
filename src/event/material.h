#ifndef MATERIAL_H
#define MATERIAL_H

static int brightness = 0;

static __u8 bright[] = {0x00, 0x1f, 0x18, 0x01};

static __u8 buf[] = {0x05, 0x00, 0x3d, 0x03, 0x06, 0x00, 0x07, 0x00, 0x0d, 0x14, 0x03, 0x1f, 0xad};

/**
 * 
 * function who activate numpad and block touchpad
 * 
 **/
void activate_numpad(const devices_info *dev_info);

/**
 * 
 * function who desactivate numpad and unlock touchpad
 * 
 **/
void deactivate_numpad(const devices_info *dev_info);

/**
 * 
 * change brightness variable
 * 
 **/
void change_brightness(const devices_info *dev_info);

/**
 * 
 * send buf with brigthness on i2c file
 * 
 **/
void i2c_send(const devices_info *dev_info);

#endif