#include <signal.h>
#include <unistd.h>
#include <linux/input.h>

#include "event.h"
#include "utility/utility.h"

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
            if (event.code == ABS_MT_POSITION_X || event.code == ABS_MT_POSITION_Y)
            {
                if (event.code == ABS_MT_POSITION_X)
                    position.x = event.value;
                else if (event.code == ABS_MT_POSITION_Y)
                    position.y = event.value;
            }
        }
        printf("(%d, %d)\n", position.x, position.y);
    }
}