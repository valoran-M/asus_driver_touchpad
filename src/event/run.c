#include <signal.h>
#include <unistd.h>
#include <linux/input.h>

#include "event.h"
#include "../init/init.h"

void run(devices_info *info)
{
    loop = 1;
    struct input_event event;
    struct
    {
        int x;
        int y;
    } position;

    signal(SIGINT, sighandler);

    while (loop)
    {
        read(info->file_touchpad, &event, sizeof(event));

        if (event.type != EV_ABS && event.type != EV_KEY)
            if (event.code != ABS_MT_POSITION_X &&
                event.code != ABS_MT_POSITION_Y &&
                event.code != BTN_TOOL_FINGER)
                continue;

        if (event.type == EV_ABS)
        {
            if (event.code == ABS_X || event.code == ABS_Y)
            {
                if (event.code == ABS_X)
                    printf("X = %d, %d\n", event.value, event.time);
                else if (event.code == ABS_Y)
                    printf("Y = %d, %d\n", event.value, event.time);
            }
        }
    }
}