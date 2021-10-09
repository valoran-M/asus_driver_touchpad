#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>

#include "utility.h"
#include "get_proc.h"

void get_devices(devices_info *dev_info) {
    FILE *devices = fopen(DEVICES_LISTE_PATH, "r");

    if (devices == NULL) {
        stop_get_proc(
                "\nsrc/init/get_proc.c -> get_devices :  Unable to open devices list\n", devices);
    }

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, devices) != NULL)
        if (strstr(line, "Name=") != NULL)
            name_analyse(dev_info, devices, line);

    if (dev_info->file_keyboard <= 0 || dev_info->file_uinput <= 0)
        stop_get_proc(
                "\nsrc/init/get_proc.c -> get_devices :  The device \"Asus Keyboard\" was not found\n",
                devices);
    else if (dev_info->file_touchpad <= 0)
        stop_get_proc(
                "\nsrc/init/get_proc.c -> get_devices :  The device \"Asus Touchpad\" was not found\n",
                devices);

    fclose(devices);
}


void name_analyse(devices_info *dev_info, FILE *devices, char *line) {
    fprintf(stderr, "LINE : %s", line);

    if (strstr(line, "Touchpad") != NULL ||
        strstr(line, "ELAN") != NULL ||
        strstr(line, "SynPS/2") != NULL) {
        get_touchpad_info(dev_info, devices, line);
    } else if (strstr(line, "AT Translated Set 2 keyboard") != NULL ||
               strstr(line, "Asus Keyboard") != NULL) {
        get_keyboard_info(dev_info, devices, line);
    }
}

int get_touchpad_info(devices_info *dev_info, FILE *devices, char *line) {
    const char *line_pointer;
    char number[5];

    while (fgets(line, MAX_LINE, devices) != NULL) {
        if (strstr(line, "Sysfs=") != NULL) {
            char i2c[] = "i2c-";
            line_pointer = strstr(line, i2c);
            if (line_pointer != NULL) {
                get_number(devices, line_pointer + sizeof(i2c) - 1, number);
                char event_file[50] = I2C_FILE;
                strcat(event_file, number);
                dev_info->i2c = open(event_file, O_RDWR);

                if (dev_info->i2c == -1) {
                    stop_get_proc("\nsrc/init/get_proc.c -> get_touchpad_info : open problems\n",
                                  devices);
                }
            } else {
                stop_get_proc(
                        "\nsrc/init/get_proc.c -> get_touchpad_info :  i2c coef is not found\n",
                        devices);
            }
        } else if (strstr(line, "Handlers=") != NULL) {
            char event[] = "event";
            line_pointer = strstr(line, event);

            if (line_pointer != NULL) {
                get_number(devices, line_pointer + sizeof(event) - 1, number);
                char event_file[50] = EVENT_FILE;
                strcat(event_file, number);
                dev_info->file_touchpad = open(event_file, O_RDWR);

                if (dev_info->file_touchpad == -1) {
                    stop_get_proc("\nsrc/init/get_proc.c -> get_touchpad_info : open problems\n",
                                  devices);
                }
                return 1;
            } else {
                stop_get_proc(
                        "\nsrc/init/get_proc.c -> get_touchpad_info :  event coef is not found\n",
                        devices);
            }
        }
    }
    return 0;
}

int get_keyboard_info(devices_info *dev_info, FILE *devices, char *line) {
    const char *line_pointer;
    char number[5];

    while (fgets(line, MAX_LINE, devices) != NULL) {
        fprintf(stderr, "LINEEE : %s", line);

        if (strstr(line, "Handlers=") != NULL) {
            char event[] = "event";
            line_pointer = strstr(line, event);

            if (line_pointer != NULL) {
                get_number(devices, line_pointer + sizeof(event) - 1, number);
                char event_file[50] = EVENT_FILE;
                strcat(event_file, number);
                dev_info->file_keyboard = open(event_file, O_RDWR);

                if (dev_info->file_keyboard == -1) {
                    stop_get_proc("\nsrc/init/get_proc.c -> get_keyboard_info : open problems\n",
                                  devices);
                }
                return 1;
            } else {
                stop_get_proc(
                        "\nsrc/init/get_proc.c -> get_keyboard_info :  event coef is not found\n",
                        devices);
            }
        }
    }
    return 0;
}

void get_number(FILE *devices, const char *line, char *number) {
    if (line == NULL)
        stop_get_proc("\nsrc/init/get_proc.c -> get_number : line = NULL\n", devices);

    int i;
    for (i = 0; isdigit(*(line + i)); i++)
        number[i] = *(line + i);

    number[i] = '\0';
}

void stop_get_proc(const char *output, FILE *devices) {
    fprintf(stderr, "%s", output);

    if (devices != NULL) {
        fclose(devices);
    }

    exit(EXIT_FAILURE);
}

