#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "init.h"
#include "get_proc.h"

devices_info *get_devices()
{
    devices_info *info = malloc(sizeof(devices_info));

    FILE *devices = fopen(DEVICES_LISTE_PATH, "r");

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, devices) != NULL)
        if (strstr(line, "Name=") != NULL)
            if (name_analyse(line) == 1)
                get_touchpad_info(devices, info, line);
            else if (name_analyse(line) == 2)
                get_keyboard_info(devices, info, line);

    fclose(devices);

    return info;
}

int name_analyse(char *line)
{
    if (strstr(line, "ASUE") != NULL)
        if (strstr(line, "Touchpad") != NULL)
            return 1;
        else if (strstr(line, "Keyboard"))
            return 2;

    return 0;
}

void get_touchpad_info(FILE *devices, devices_info *info, char *line)
{
    char string_int[10];
    char *line_pointer;
    touchapd = 1;
    while (fgets(line, MAX_LINE, devices) != NULL)
        if (strstr(line, "Sysfs=") != NULL)
        {
            if ((line_pointer = strstr(line, "i2c-")) != NULL)
            {
                line_pointer += 4;
                int i;
                for (i = 0; isdigit(*(line_pointer + i)); i++)
                    string_int[i] = *(line_pointer + i);
                string_int[i] = '\0';
                info->i2c = atoi(string_int);
                return;
            }
            else
            {
                printf("LLLL");
                return;
            }
        }
}

void get_keyboard_info(FILE *devices, devices_info *info, char *line)
{
    keyboard = 1;
}