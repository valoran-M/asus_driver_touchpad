#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "defines.h"

/**
 *
 * run driver
 * 
 **/
void run(devices_info *dev_info);

int ready_to_read(int fd);

#endif  // EVENT_LOOP_H
