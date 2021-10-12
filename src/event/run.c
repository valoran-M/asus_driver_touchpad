#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <linux/input.h>
#include <sys/poll.h>

#include "event.h"
#include "material.h"
#include "utility/utility.h"
#include "run.h"


int running = 1;

void sighandler(int sig)
{
    running = 0;
}

void run(const devices_info *dev_info)
{
    struct input_event event;
    struct
    {
        int x;
        int y;
    } position;
    int numlock = 0, finger = 0;
    int col = 0, line = 0;
    key value = (key) {-1, -1};
    position.x = 0;
    position.y = 0;

    signal(SIGINT, sighandler);

    emit(dev_info, EV_KEY, KEY_NUMLOCK, 0);

    while (running) {

        if (ready_to_read(dev_info->file_touchpad)) {
            read(dev_info->file_touchpad, &event, sizeof(event));
        }else {
            continue;
        }

        if (event.type == EV_ABS) {
            if (event.code == ABS_MT_POSITION_X) {
                position.x = event.value;
            }
            else if (event.code == ABS_MT_POSITION_Y) {
                position.y = event.value;
            }
            continue;
        }

        if (event.code == BTN_TOOL_FINGER) {
            if (event.value == 0) {
                finger = 0;
                if (value.shifted != -1) {
                    remove_key(dev_info, value);
                    value = (key) {-1, -1};
                }
            }
            if (event.value == 1 && finger == 0) {
                finger = 1;
            }

            if (event.value == 1 &&
                (position.x > 0.95 * (double) dev_info->x.max &&
                 position.y < 0.09 * (double) dev_info->y.max)) {
                finger = 0;
                numlock = !numlock;
                if (numlock) {
                    activate_numpad(dev_info);
                }
                else {
                    deactivate_numpad(dev_info);
                }
            }
            else if (event.value == 1 &&
                     (position.x < 0.06 * (double) dev_info->x.max &&
                      position.y < 0.07 * (double) dev_info->y.max)) {
                finger = 0;
                change_brightness(dev_info);
            }

            if (numlock) {
                if (finger == 1) {
                    finger = 2;

                    col = floor((double) dev_info->colonne * (double) position.x /
                                (double) dev_info->x.max);
                    line = floor(((double) dev_info->line * (double) position.y /
                                  (double) dev_info->y.max) -
                                 0.3);

                    if (line >= 0) {
                        value = dev_info->keys[line][col];
                        emit_key(dev_info, value);
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

    if (poll(&fds, 1, 1000) > 0) {  // 1000 ms : timeout
        return fds.revents & POLLIN;
    }

    return 0;
}
