#ifndef KEY_EVENTS_H
#define KEY_EVENTS_H

#include "defines.h"
#include "interface.h"

/**
 * emit key with key struct param
 * 
 * @param key
 * 
 **/
void press_key(const devices_info *dev_info, key k);

/**
 * remove key with key struct param
 * 
 * @param key
 * 
 **/
void release_key(const devices_info *dev_info, key k);

/**
 *
 * function who activate numpad and block touchpad
 *
 **/
void activate_numpad(devices_info *dev_info);

/**
 *
 * function who desactivate numpad and unlock touchpad
 *
 **/
void deactivate_numpad(devices_info *dev_info);

/**
 *
 * change brightness variable
 *
 **/
void change_brightness(devices_info *dev_info);

#endif  // KEY_EVENTS_H