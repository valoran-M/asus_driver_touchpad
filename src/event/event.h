#ifndef EVENT_H
#define EVENT_H

#include "utility/utility.h"

/**
 * emit key with key struct param
 * 
 * @param key
 * 
 **/
void emit_key(const devices_info *dev_info, key k);

/**
 * remove key with key struct param
 * 
 * @param key
 * 
 **/
void remove_key(const devices_info *dev_info, key k);

/**
 * emit a event
 * 
 * @param int event type
 * @param int event code
 * @param int event val
 * 
 **/
void emit(const devices_info *dev_info, int type, int code, int val);

#endif