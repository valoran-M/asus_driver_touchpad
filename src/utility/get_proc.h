#ifndef GET_PROC_H
#define GET_PROC_H

#include <stdio.h>

#include "utility.h"

#define I2C_FILE "/dev/i2c-"
#define EVENT_FILE "/dev/input/event"
#define DEVICES_LISTE_PATH "/proc/bus/input/devices"
#define MAX_LINE 500


/**
 *
 * setup devices_info
 *
 **/
void get_devices(devices_info *dev_info);

/**
 * name analyser in devices file
 * 
 * @param char*     line to scan
 *
 **/
void name_analyse(devices_info *dev_info, FILE *devices, char *line);

/**
 * get information for touchpad event
 * 
 * @param char* string for file's lines
 * 
 **/
int get_touchpad_info(devices_info *dev_info, FILE *devices, char *line);

/**
 * get information for keyboard event
 * 
 * @param char* string for file's lines
 * 
 **/
int get_keyboard_info(devices_info *dev_info, FILE *devices, char *line);

/**
 * 
 * get first number in string
 * 
 * @param char* line
 * @param char* number in string 
 * 
 **/
void get_number(FILE *devices, const char *line, char *number);

/**
 * 
 * stop get_proc when FAILURE
 * 
 * @param char* output
 * 
 **/
void stop_get_proc(const char *output, FILE *devices);

#endif