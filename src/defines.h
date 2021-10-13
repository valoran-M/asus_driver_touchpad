#ifndef DEFINES_H
#define DEFINES_H

#define I2C_PATH "/dev/"
#define EVENT_DIR "/dev/input/"
#define DEVICES_LISTE_PATH "/proc/bus/input/devices"
#define UINPUT_FILE "/dev/uinput"
#define DEVICE_REGEX "Name=\"(.*touchpad.*)\"\n.*\n.*\n?.*sysfs=(.*)\n.*\n.*\n?.*handlers=.*(events[0-9]*).*"
#define I2C_REGEX "i2c-[0-9]*"
#define DEVICE_MATCH_NUMBER 4
#define BUFFER_SIZE 10000


typedef struct
{
    double x;
    double y;
} point;


typedef struct
{
    int shifted;
    int key;
} key;

typedef struct
{
    int file_touchpad;
    int file_uinput;
    int i2c;
    double max_x;
    double max_y;

    key **keys;
    unsigned int line;
    unsigned int colonne;
} devices_info;

#endif  // DEFINES_H