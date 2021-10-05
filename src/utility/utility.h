#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>

struct abs_info
{
    int max;
    int min;
};

typedef struct
{
    int file_touchpad;
    int file_keyboard;
    int file_uinput;
    int i2c;
    struct abs_info x;
    struct abs_info y;
} devices_info;

/** 
 * 
 * @return pointer to struct devices_info
 * 
 **/
devices_info *get_devices();

/**
 * add max and min in devices_info
 * 
 * @param devices_info* info
 * 
 **/
void max_min(devices_info *info);

/**
 * 
 * frees the heap
 * 
 * @param devices_info*
 * 
 **/
void stop(devices_info *info);

#endif