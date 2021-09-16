#include <stdio.h>
#include <stdlib.h>

#include "init.h"

#define DEVICES_LISTE_PATH "/proc/bus/input/devices"

devices_info* get_devices()
{
    devices_info *info = malloc(sizeof(devices_info));

    FILE *devices = fopen(DEVICES_LISTE_PATH, "r");

    fclose(devices);
    
    return info;
}