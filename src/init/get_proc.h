#ifndef GET_PROC_H
#define GET_PROC_H

#include <stdio.h>

#include "init.h"

#define DEVICES_LISTE_PATH "/proc/bus/input/devices"
#define MAX_LINE 500

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
 * @param FILE* file where information devices are stocked
 * @param devices_info* struct for différent information
 * @param char* string for file's lines
 * 
 **/
void get_touchpad_info(FILE *devices, devices_info *info, char *line);

/**
 * get information for keyboard event
 * 
 * @param FILE* file where information devices are stocked
 * @param devices_info* struct for différent information
 * @param char* string for file's lines
 * 
 **/
void get_keyboard_info(FILE *devices, devices_info *info, char *line);

#endif