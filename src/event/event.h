#ifndef EVENT_H
#define EVENT_H

/**
 * signal handler
 * 
 * @param int type of signal
 * 
 **/
void sighandler(int);

#include "utility/utility.h"

/**
 * emit key with key struct param
 * 
 * @param key
 * 
 **/
void emit_key(key k);

/**
 * remove key with key struct param
 * 
 * @param key
 * 
 **/
void remove_key(key k);

/**
 * emit a event
 * 
 * @param int event type
 * @param int event code
 * @param int event val
 * 
 **/
void emit(int type, int code, int val);

#endif