#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

#ifndef I2C_M_RD

#include <linux/i2c.h>

#endif

#include "interface.h"

static __u8 bright[] = {0x00, 0x1f, 0x18, 0x01};
static __u8 buf[] = {0x05, 0x00, 0x3d, 0x03, 0x06, 0x00, 0x07, 0x00, 0x0d, 0x14, 0x03, 0x1f, 0xad};

void emit(devices_info *dev_info, unsigned short type, unsigned short code, int val)
{
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    size_t to_write = sizeof(ie);

    if (write(dev_info->file_uinput, &ie, to_write) != to_write) {
        error("Failed to emit key.", dev_info);
    }
}

void i2c_send(devices_info *dev_info)
{

    if (dev_info->file_i2c == -1) {
        return;
    } // Working without file_i2c

    buf[11] = bright[dev_info->brightness];

    struct i2c_msg message[] = {
            {
                    .addr = (__u16) 0x15,
                    .buf = buf,
                    .len = (__u16) 13,
            },
    };

    struct i2c_rdwr_ioctl_data payload =
            {
                    .msgs = message,
                    .nmsgs = sizeof(message) / sizeof(message[0]),
            };

    check_ioctl(ioctl(dev_info->file_i2c, I2C_RDWR, &payload), dev_info);
}