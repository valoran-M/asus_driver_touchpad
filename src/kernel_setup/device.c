#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <linux/uinput.h>

#include "device.h"

void get_devices(devices_info *dev_info)
{
    char *buffer = read_device_list();

    regex_t regex;
    regmatch_t matches[DEVICE_MATCH_NUMBER];

    if (regcomp(&regex, DEVICE_REGEX, REG_ICASE | REG_EXTENDED | REG_NEWLINE)) {
        free(buffer);
        error("Unable to compile device regex.\n");
    }

    if (regexec(&regex, buffer, DEVICE_MATCH_NUMBER, matches, 0) == 0) {
        regfree(&regex);

        char *match_buffer = NULL;
        extract_match(matches, 1, &match_buffer, buffer);
        printf("Device Name : '%s'\n", match_buffer);

        extract_match(matches, 3, &match_buffer, buffer);
        open_touchpad(dev_info, buffer, match_buffer);

        extract_match(matches, 2, &match_buffer, buffer);
        open_i2c(dev_info, buffer, match_buffer);

        free(match_buffer);
        free(buffer);
    }
    else {
        regfree(&regex);
        free(buffer);
        error("No regex match. Unable to find a proper device.\n");
    }
}

void open_touchpad(devices_info *dev_info, char *buffer, char *match_buffer)
{
    char *event_filepath = malloc(strlen(EVENT_PATH) + strlen(match_buffer) + 1);

    if (event_filepath == NULL) {
        free(match_buffer);
        free(buffer);
        error("Bad alloc (event_filepath@open_touchpad).\n");
    }

    strcpy(event_filepath, EVENT_PATH);
    strcpy(event_filepath + strlen(EVENT_PATH), match_buffer);

    printf("Event Path : '%s'\n", event_filepath);

    int fd = open(event_filepath, O_RDWR); // Check if other flags are needed...
    free(event_filepath);

    if (fd == -1) {
        free(match_buffer);
        free(buffer);
        error("Unable to open touchpad events file.\n");
    }

    dev_info->file_touchpad = fd;
}

void open_i2c(devices_info *dev_info, char *buffer, char *match_buffer)
{
    regex_t i2c_regex;
    regmatch_t i2c_match;

    if (regcomp(&i2c_regex, I2C_REGEX, REG_ICASE | REG_EXTENDED)) {
        free(match_buffer);
        free(buffer);
        error("Failed to compile file_i2c regex.\n");
    }

    int fd = -1;

    if (regexec(&i2c_regex, match_buffer, 1, &i2c_match, 0) == 0) {
        regfree(&i2c_regex);

        char *i2c_file = NULL;
        size_t match_size = i2c_match.rm_eo - i2c_match.rm_so;

        i2c_file = malloc(match_size + 1);
        if (i2c_file == NULL) {
            free(match_buffer);
            free(buffer);
            error("Bad alloc (i2c_file@open_i2c).\n");
        }
        strncpy(i2c_file, match_buffer + i2c_match.rm_so, match_size);
        i2c_file[match_size] = '\0';

        char *i2c_filepath = malloc(strlen(I2C_PATH) + strlen(i2c_file) + 1);

        if (i2c_filepath == NULL) {
            free(i2c_file);
            free(match_buffer);
            free(buffer);
            error("Bad alloc (i2c_filepath@open_i2c).\n");
        }

        strcpy(i2c_filepath, I2C_PATH);
        strcat(i2c_filepath + strlen(I2C_PATH), i2c_file);
        free(i2c_file);

        printf("I2C Path : '%s'\n", i2c_filepath);

        fd = open(i2c_filepath, O_RDWR); // Check if other flags are needed...
        free(i2c_filepath);

        if (fd == -1) {
            warning("Failed to open file_i2c file. file_i2c feedback disabled.\n");
        }
    }
    else {
        regfree(&i2c_regex);
        warning("No file_i2c devices detected. file_i2c feedback disabled.\n");
    }

    dev_info->file_i2c = fd;
}

char *read_device_list()
{
    int devices = open(DEVICES_LIST, O_RDONLY);
    if (devices == -1) {
        error("Failed to open devices file list.\n");
    }

    char *buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        error("Bad alloc (buffer@read_device_list).\n");
    }

    long result = read(devices, buffer, BUFFER_SIZE);
    if (result == -1) {
        free(buffer);
        error("Unable to read devices list.\n");
    }

    if (close(devices)) {
        free(buffer);
        error("Failed to close devices file list.\n");
    }

    printf("Read bytes : %lu\n", result);

    if (result == BUFFER_SIZE) {
        warning("Read bytes number equal buffer size. Working on a possible chunk of device list.\n");
    }
    else {
        buffer = realloc(buffer, result + 1);  // Make a proper string with a '\0' at the end.
        buffer[result] = '\0';
    }

    return buffer;
}

void extract_match(const regmatch_t *matches, size_t i, char **match_buffer, char *buffer)
{
    size_t match_size = matches[i].rm_eo - matches[i].rm_so;

    *match_buffer = realloc(*match_buffer, match_size + 1);
    if (*match_buffer == NULL) {
        free(buffer);
        error("Bad alloc (*match_buffer@extract_match).\n");
    }
    strncpy(*match_buffer, buffer + matches[i].rm_so, match_size);

    (*match_buffer)[match_size] = '\0';
}

void max_min(devices_info *dev_info)
{
    int abs[5] = {0};

    check_ioctl(ioctl(dev_info->file_touchpad, EVIOCGABS(ABS_X), abs));
    dev_info->min.x = (double) abs[1];
    dev_info->max.x = (double) abs[2];

    check_ioctl(ioctl(dev_info->file_touchpad, EVIOCGABS(ABS_Y), abs));
    dev_info->min.y = (double) abs[1];
    dev_info->max.y = (double) abs[2];
}
