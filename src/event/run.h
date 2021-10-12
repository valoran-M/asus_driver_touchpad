#ifndef RUN_H
#define RUN_H

#include <stdbool.h>
#include "../utility/utility.h"

/**
 * 
 * run driver
 * 
 **/
void run(const devices_info *dev_info);

int ready_to_read(int fd);

#endif