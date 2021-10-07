#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <linux/input.h>

#include "event.h"
#include "material.h"
#include "utility/utility.h"

void run()
{
    struct input_event event;
    struct
    {
        int x;
        int y;
    } position;
    int numlock = 0, finger = 0;
    int col = 0, line = 0;
    key value = (key){-1, -1};
    position.x = 0;
    position.y = 0;

    signal(SIGINT, sighandler);

    emit(EV_KEY, KEY_NUMLOCK, 0);

    while (1)
    {
        read(info->file_touchpad, &event, sizeof(event));

        if (event.type != EV_ABS &&
            event.type != EV_KEY &&
            event.code != ABS_MT_POSITION_X &&
            event.code != ABS_MT_POSITION_Y &&
            event.code != BTN_TOOL_FINGER)
            continue;

        if (event.type == EV_ABS && (event.code == ABS_MT_POSITION_X ||
                                     event.code == ABS_MT_POSITION_Y))
        {
            if (event.code == ABS_MT_POSITION_X)
                position.x = event.value;
            else if (event.code == ABS_MT_POSITION_Y)
                position.y = event.value;
            continue;
        }

        if (event.code == BTN_TOOL_FINGER)
        {
            if (event.value == 0)
            {
                finger = 0;
                if (value.shifted != -1)
                {
                    remove_key(value);
                    value = (key){-1, -1};
                }
            }
            if (event.value == 1 && finger == 0)
                finger = 1;

            if (event.value == 1 &&
                (position.x > 0.95 * (double)info->x.max &&
                 position.y < 0.09 * (double)info->y.max))
            {
                finger = 0;
                numlock = !numlock;
                if (numlock)
                    activate_numpad();
                else
                    desactivate_numpad();
            }
            else if (event.value == 1 &&
                     (position.x < 0.06 * (double)info->x.max &&
                      position.y < 0.07 * (double)info->y.max))
            {
                finger = 0;
                change_brightness();
            }

            if (numlock)
            {
                if (finger == 1)
                {
                    finger = 2;

                    col = floor((double)info->colonne * (double)position.x / (double)info->x.max);
                    line = floor(((double)info->line * (double)position.y / (double)info->y.max) - 0.3);

                    if (line >= 0)
                    {
                        value = info->keys[line][col];
                        emit_key(value);
                    }
                }
            }
        }
    }
}