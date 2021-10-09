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
    int shifted;
    int key;
} key;

typedef struct
{
    int file_touchpad;
    int file_keyboard;
    int file_uinput;
    int i2c;
    struct abs_info x;
    struct abs_info y;

    key **keys;
    int line;
    int colonne;
} devices_info;

//devices_info *info;

/**
 * 
 * add max and min in devices_info
 * 
 **/
void max_min(devices_info *dev_info);

/**
 * 
 * frees the heap
 * 
 **/
void stop(devices_info *dev_info);

#endif