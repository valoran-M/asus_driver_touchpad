#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int *file_mouse;
    int *file_keyboard;
} devices_info;

devices_info* get_devices();

#endif