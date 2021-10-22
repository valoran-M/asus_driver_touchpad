#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <linux/input.h>
#include <sys/poll.h>
#include <stdio.h>

#include "utils/keymap.h"

#include "event_loop.h"
#include "interface.h"
#include "keys_events.h"

int running = 1;

void sig_handler()
{
    running = 0;
}

void run(devices_info *dev_info)
{
    struct input_event event;
    point position = {0, 0};
    int numlock = 0;
    int finger = 0;

    unsigned short col;
    unsigned short line;

    key value = (key) {-1, -1};

    signal(SIGINT, &sig_handler);

    emit(dev_info, EV_KEY, KEY_NUMLOCK, 0);

    while (running) {

        if (ready_to_read(dev_info->file_touchpad)) {
            read(dev_info->file_touchpad, &event, sizeof(event));
        }
        else {
            continue;
        }

        if (event.code == ABS_MT_POSITION_X) {
            position.x = (event.value - dev_info->min.x) / dev_info->range.x;
        }
        else if (event.code == ABS_MT_POSITION_Y) {
            position.y = (event.value - dev_info->min.y) / dev_info->range.y;
        }
        else if (event.code == BTN_TOOL_FINGER) {
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

            if (numlock && finger == 1) {
                finger = 2;

                col = (short) floor(dev_info->mapping.colonne * position.x);
                line = (short) floor((dev_info->mapping.line * position.y) - 0.3);
                // Le - 0.3 est-il obligatoirement nécessaire sur ton touchpad ?
                // Ça fonctionne super bien sur le mien sans

                press_key(dev_info, keymap_get(dev_info, line, col));
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
