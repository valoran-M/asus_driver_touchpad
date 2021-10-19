#ifndef DEVICE_H
#define DEVICE_H

#include <regex.h>
#include "defines.h"
#include "error.h"

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
 * Open touchpad events file and store the new descriptor in dev_info->file_touchpad
 *
 * @param dev_info* dev_info : dev_info struct to store in
 * @param char* buffer : pointer to free if an error occurs
 * @param char* match_buffer : events file name
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
 * add max and min in devices_info
 *
 **/
void max_min(devices_info *dev_info);

#endif // DEVICE_H