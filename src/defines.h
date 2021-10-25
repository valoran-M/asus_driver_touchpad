#ifndef DEFINES_H
#define DEFINES_H

#define I2C_PATH "/dev/"
#define EVENT_PATH "/dev/input/"

#define DEVICES_LIST "/proc/bus/input/devices"
#define UINPUT_FILE "/dev/uinput"

#define DEVICE_REGEX "Name=\"(.*touchpad.*)\"\n.*\n.*\n?.*sysfs=(.*)\n.*\n.*\n?.*handlers=.*(event[0-9]*).*"
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
    unsigned char shifted;
    unsigned short key;
} key;

typedef struct
{
    unsigned short line;
    unsigned short colonne;
    key *keys;
} keymap;

typedef struct
{
    int file_touchpad;
    int file_uinput;
    int file_i2c;
    unsigned short brightness;

    point range;
    point min;

    keymap mapping;
} devices_info;

#endif  // DEFINES_H