#ifndef GET_PROC_H
#define GET_PROC_H

#include <stdio.h>

#include "utility.h"

#define I2C_FILE "/dev/i2c-"
#define EVENT_FILE "/dev/input/event"
#define DEVICES_LISTE_PATH "/proc/bus/input/devices"
#define MAX_LINE 500

static FILE *devices;

static int touchapd = 0, keyboard = 0;

/**
 * name analyser in devices file
 * 
 * @param char*     line to scan
 * 
 * @return 0 if nothing / 1 if Touchpad / 2 Keyboard
 * 
 **/
int name_analyse(char *);

/**
 * get information for touchpad event
 * 
 * @param char* string for file's lines
 * 
 **/
void get_touchpad_info(char *line);

/**
 * get information for keyboard event
 * 
 * @param char* string for file's lines
 * 
 **/
void get_keyboard_info(char *line);

/**
 * 
 * get first number in string
 * 
 * @param char* line
 * @param char* number in string 
 * 
 **/
void get_number(char *line, char *number);

/**
 * 
 * stop get_proc when FAILURE
 * 
 * @param char* output
 * 
 **/
void stop_get_proc(char *output);

#endif