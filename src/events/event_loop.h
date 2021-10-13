#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "defines.h"

/**
 * 
 * run driver
 * 
 **/
void run(const devices_info *dev_info);

int ready_to_read(int fd);

/**
 *
 * frees the heap
 *
 **/
void stop(devices_info *dev_info);

#endif  // EVENT_LOOP_H