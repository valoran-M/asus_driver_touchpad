#ifndef GET_PROC_H
#define GET_PROC_H

#include <stdio.h>
#include <regex.h>

#include "utility.h"

#define I2C_PATH "/dev/"
#define EVENT_DIR "/dev/input/"
#define DEVICES_LISTE_PATH "/proc/bus/input/devices"
#define DEVICE_REGEX "Name=\"(.*touchpad.*)\"\n.*\n.*\n?.*sysfs=(.*)\n.*\n.*\n?.*handlers=.*(event[0-9]*).*"
#define I2C_REGEX "i2c-[0-9]*"
#define DEVICE_MATCH_NUMBER 4
#define BUFFER_SIZE 10000


/**
 *
 * Detected interesting device and store their opened file in the passed structure
 *
 * @param devices_info *dev_info : the struct witch will be initialized
 *
 **/
void get_devices(devices_info *dev_info);

/**
 *
 * Read the device list file
 *
 * @return char* allocated buffer of the whole file
 *
 **/
char *read_device_list();

/**
 *
 * Extract the regex match number i and store it into *match_buffer
 *
 * @param const regmatch_t *matches : list of regex matches
 * @param size_t i : position in the array of the selected match to extract
 * @param char **match_buffer : pointer to the char array witch will receive the extracted data
 * @param char *buffer : buffer to free in case of failure
 *
 **/
void extract_match(const regmatch_t *matches, size_t i, char **match_buffer, char *buffer);

/**
 *
 * Open touchpad event file and store the new descriptor in dev_info->file_touchpad
 *
 * @param dev_info* dev_info : dev_info struct to store in
 * @param char* buffer : pointer to free if an error occurs
 * @param char* match_buffer : event file name
 *
 **/
void open_touchpad(devices_info *dev_info, char *buffer, char *match_buffer);

/**
 *
 * Open i2c file and store the new descriptor in dev_info->file_i2c
 *
 * @param dev_info* dev_info : dev_info struct to store in
 * @param char* buffer : pointer to free if an error occurs
 * @param char* match_buffer : i2c file name
 *
 **/
void open_i2c(devices_info *dev_info, char *buffer, char *match_buffer);

/**
 * 
 * stop get_proc when FAILURE
 * 
 * @param char* output
 * 
 **/
void stop_get_proc(const char *output);

#endif