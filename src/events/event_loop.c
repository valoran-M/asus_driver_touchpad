#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <linux/input.h>
#include <sys/poll.h>
#include <stdlib.h>
#include <linux/uinput.h>

#include "event_loop.h"
#include "interface.h"
#include "keys_events.h"

int running = 1;

void sighandler(int sig)
{
    running = 0;
}

void stop(devices_info *dev_info)
{
    close(dev_info->file_touchpad);
    if (dev_info->i2c != -1) {
        close(dev_info->i2c);
    }

    ioctl(dev_info->file_uinput, UI_DEV_DESTROY);
    close(dev_info->file_uinput);

    for (size_t i = 0; i < dev_info->line; i++) {
        free(dev_info->keys[i]);
    }
    free(dev_info->keys);

    exit(EXIT_SUCCESS);
}

void run(const devices_info *dev_info)
{
    struct input_event event;
    point position;
    int numlock = 0, finger = 0;
    int col = 0, line = 0;
    key value = (key) {-1, -1};
    position.x = 0;
    position.y = 0;
    position.x = 0;
    position.y = 0;

    signal(SIGINT, sighandler);

    emit(dev_info, EV_KEY, KEY_NUMLOCK, 0);

    while (running) {

        if (ready_to_read(dev_info->file_touchpad)) {
            read(dev_info->file_touchpad, &event, sizeof(event));
        }
        else {
            continue;
        }

        if (event.type == EV_ABS) {
            if (event.code == ABS_MT_POSITION_X) {
                position.x = event.value / dev_info->max_x;
            }
            else if (event.code == ABS_MT_POSITION_Y) {
                position.y = event.value / dev_info->max_y;
            }
            continue;
        }

        if (event.code == BTN_TOOL_FINGER) {
            if (event.value == 0) {
                finger = 0;
                if (value.shifted != -1) {
                    release_key(dev_info, value);
                    value = (key) {-1, -1};
                }
            }
            if (event.value == 1 && finger == 0) {
                finger = 1;
            }

            if (event.value == 1 && position.x > 0.95 && position.y < 0.09) {
                finger = 0;
                numlock = !numlock;
                if (numlock) {
                    activate_numpad(dev_info);
                }
                else {
                    deactivate_numpad(dev_info);
                }
            }
            else if (event.value == 1 && position.x < 0.06 && position.y < 0.07) {
                finger = 0;
                if (numlock) {
                    change_brightness(dev_info);
                }
            }

            if (numlock) {
                if (finger == 1) {
                    finger = 2;

                    col = (int) floor((double) dev_info->colonne * position.x);
                    line = (int) floor(((double) dev_info->line * position.y) - 0.3);

                    if (line >= 0) {
                        value = dev_info->keys[line][col];
                        press_key(dev_info, value);
                    }
                }
            }
        }
    }
}

int ready_to_read(int fd)
{
    static struct pollfd fds;
    fds.fd = fd;
    fds.events = POLLIN;

    if (poll(&fds, 1, 1000) > 0) { // 1000 ms : timeout
        return fds.revents & POLLIN;
    }

    return 0;
}
