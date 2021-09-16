#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>

#include "init.h"
#include "get_proc.h"

devices_info *get_devices()
{
    info = malloc(sizeof(devices_info));

    devices = fopen(DEVICES_LISTE_PATH, "r");

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, devices) != NULL)
        if (strstr(line, "Name=") != NULL)
            name_analyse(line);

    fclose(devices);

    return info;
}

int name_analyse(char *line)
{
    if (strstr(line, "ASUE") != NULL)
        if (strstr(line, "Touchpad") != NULL)
            get_touchpad_info(line);
        else if (strstr(line, "Keyboard"))
            get_keyboard_info(line);

    return 0;
}

void get_touchpad_info(char *line)
{
    char *line_pointer;
    char number[5];
    touchapd = 1;
    while (fgets(line, MAX_LINE, devices) != NULL)
        if (strstr(line, "Sysfs=") != NULL)
        {
            char i2c[] = "i2c-";
            if ((line_pointer = strstr(line, i2c)) != NULL)
            {
                get_number(line_pointer + sizeof(i2c) - 1, number);
                info->i2c = atoi(number);
            }
            else
                stop_get_proc("src/init/get_proc.c -> get_touchpad_info :  i2c coef is not found\n");
        }
        else if (strstr(line, "Handlers=") != NULL)
        {
            char event[] = "event";
            if ((line_pointer = strstr(line, event)) != NULL)
            {
                get_number(line_pointer + sizeof(event) - 1, number);
                char event_file[50] = EVENT_FILE;
                if ((info->file_touchpad = open(strcat(event_file, number), O_RDONLY | O_CREAT)) == -1)
                    stop_get_proc("src/init/get_proc.c -> get_touchpad_info : open problems\n");
                break;
            }
            else
                stop_get_proc("src/init/get_proc.c -> get_touchpad_info :  event coef is not found\n");
        }
}

void get_keyboard_info(char *line)
{
    char *line_pointer;
    char number[5];
    keyboard = 1;

    while (fgets(line, MAX_LINE, devices) != NULL)
        if (strstr(line, "Handlers=") != NULL)
        {
            char event[] = "event";
            if ((line_pointer = strstr(line, event)) != NULL)
            {
                get_number(line_pointer + sizeof(event) - 1, number);
                char event_file[50] = EVENT_FILE;
                if ((info->file_keyboard = open(strcat(event_file, number), O_RDONLY | O_CREAT)) == -1)
                    stop_get_proc("src/init/get_proc.c -> get_keyboard_info : open problems\n");
                break;
            }
            else
                stop_get_proc("src/init/get_proc.c -> get_keyboard_info :  event coef is not found\n");
        }
}

void get_number(char *line, char *number)
{
    if (line == NULL)
        stop_get_proc("src/init/get_proc.c -> get_number : line = NULL\n");

    int i;
    for (i = 0; isdigit(*(line + i)); i++)
        number[i] = *(line + i);

    number[i] = '\0';
}

void stop_get_proc(char *output)
{
    fprintf(stderr, output);
    fclose(devices);
    stop(info);
    exit(EXIT_FAILURE);
}