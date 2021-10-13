#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <linux/uinput.h>

#include "device.h"

void warning(const char *output)
{
    fprintf(stderr, "%s", output);
}


__attribute__((noreturn))
void stop_get_proc(const char *output)
{
    fprintf(stderr, "%s", output);
    exit(EXIT_FAILURE);
}

void get_devices(devices_info *dev_info)
{
    char *buffer = read_device_list();

    regex_t regex;
    regmatch_t matches[DEVICE_MATCH_NUMBER];

    if (regcomp(&regex, DEVICE_REGEX, REG_ICASE | REG_EXTENDED | REG_NEWLINE)) {
        free(buffer);
        stop_get_proc("\nsrc/init/get_proc.c -> get_devices :  Unable to compile regex.\n");
    }

    if (regexec(&regex, buffer, DEVICE_MATCH_NUMBER, matches, 0) == 0) {
        regfree(&regex);

        char *match_buffer = NULL;
        extract_match(matches, 0, &match_buffer, buffer);
        printf("Match : '%s'", match_buffer);

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
        stop_get_proc(
                "\nsrc/init/get_proc.c -> get_devices :  Unable to find desired substrings.\n");
    }
}

void open_touchpad(devices_info *dev_info, char *buffer, char *match_buffer)
{
    char *event_filepath = malloc(strlen(EVENT_PATH) + strlen(match_buffer) + 1);

    if (event_filepath == NULL) {
        free(match_buffer);
        free(buffer);
        stop_get_proc("\nsrc/init/get_proc.c -> get_devices :  Bad alloc.\n");
    }

    strcpy(event_filepath, EVENT_PATH);
    strcpy(event_filepath + strlen(EVENT_PATH), match_buffer);

    printf("Event Path : '%s'\n", event_filepath);

    int fd = open(event_filepath, O_RDWR); // Check if other flags are needed...

    if (fd == -1) {
        free(event_filepath);
        free(match_buffer);
        free(buffer);
        stop_get_proc(
                "\nsrc/init/get_proc.c -> get_devices :  Unable to open touchpad events file.\n");
    }
    dev_info->file_touchpad = fd;

    free(event_filepath);
}

void open_i2c(devices_info *dev_info, char *buffer, char *match_buffer)
{
    regex_t i2c_regex;
    regmatch_t i2c_match;

    if (regcomp(&i2c_regex, I2C_REGEX, REG_ICASE | REG_EXTENDED)) {
        free(match_buffer);
        free(buffer);
        stop_get_proc("\nsrc/init/get_proc.c -> get_devices :  Unable to compile regex.\n");
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
            stop_get_proc("\nbuffer/init/get_proc.c -> get_devices :  Bad alloc.\n");
        }
        strncpy(i2c_file, match_buffer + i2c_match.rm_so, match_size);
        i2c_file[match_size] = '\0';

        char *i2c_filepath = malloc(strlen(I2C_PATH) + strlen(i2c_file) + 1);

        if (i2c_filepath == NULL) {
            free(i2c_file);
            free(match_buffer);
            free(buffer);
            stop_get_proc("\nsrc/init/get_proc.c -> get_devices :  Bad alloc.\n");
        }

        strcpy(i2c_filepath, I2C_PATH);
        strcat(i2c_filepath + strlen(I2C_PATH), i2c_file);
        free(i2c_file);

        printf("I2C Path : '%s'\n", i2c_filepath);

        fd = open(i2c_filepath, O_RDWR); // Check if other flags are needed...

        if (fd == -1) {
            warning("Unable to open i2c file. Working without.\n");
        }

        free(i2c_filepath);
    }
    else {
        regfree(&i2c_regex);
        warning("i2c device not detected. Working without.\n");
    }

    dev_info->i2c = fd;
}

char *read_device_list()
{
    int devices = open(DEVICES_LIST, O_RDONLY);
    if (devices == -1) {
        stop_get_proc("\nsrc/init/get_proc.c -> get_devices :  Unable to open devices list\n");
    }

    char *buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        stop_get_proc("\nsrc/init/get_proc.c -> get_devices :  Bad alloc.\n");
    }

    long result = read(devices, buffer, BUFFER_SIZE);
    if (result == -1) {
        free(buffer);
        stop_get_proc("\nsrc/init/get_proc.c -> get_devices :  Unable to read devices list.\n");
    }

    if (close(devices)) {
        free(buffer);
        stop_get_proc("\nsrc/init/get_proc.c -> get_devices :  Unable to close devices list.\n");
    }

    printf("Read bytes : %lu\n", result);

    if (result == BUFFER_SIZE) {
        warning("Warning : read bytes number equal buffer size. Working on a possible chunk of device list\n");
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
        stop_get_proc("\nbuffer/init/get_proc.c -> get_devices :  Bad alloc.\n");
    }
    strncpy(*match_buffer, buffer + matches[i].rm_so, match_size);

    (*match_buffer)[match_size] = '\0';
}

void max_min(devices_info *dev_info)
{
    int abs[3] = {0}; // TO CHECK : 6 int isn't too wide ?

    ioctl(dev_info->file_touchpad, EVIOCGABS(ABS_X), abs);
    dev_info->max_x = (double) abs[2];

    ioctl(dev_info->file_touchpad, EVIOCGABS(ABS_Y), abs);
    dev_info->max_y = (double) abs[2];
}
