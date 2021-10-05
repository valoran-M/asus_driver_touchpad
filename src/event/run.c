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

    struct input_event input;
    struct input_event input_stop;

    input.type = EV_KEY;
    input.value = 0;
    input.code = KEY_A;

    input_stop.type = EV_SYN;
    input_stop.value = 0;
    input_stop.code = SYN_REPORT;

    while (loop)
    {
        read(info->file_touchpad, &event, sizeof(event));
        write(info->file_keyboard, (const void *)&input, sizeof(input));
        write(info->file_keyboard, (const void *)&input_stop, sizeof(input));

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