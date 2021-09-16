#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *file_mouse;
    int *file_keyboard;
    int i2c;
} devices_info;

/** 
 * 
 * @return pointer to struct devices_info
 * 
 **/
devices_info *get_devices();

#endif