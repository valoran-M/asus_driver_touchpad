#include <string.h>
#include <linux/input-event-codes.h>

#include "models.h"

void init_models(devices_info *dev_info, int argc, char const *args[])
{
    if (argc < 2)
        models_selections(dev_info, basic);
    else
    {
        printf("%s\n", args[1]);
        printf("%d\n", strcmp("ux581l", args[1]) == 0);
        if (strcmp("ux581l", args[1]) == 0)
            models_selections(dev_info, ux581l);
        else
            models_selections(dev_info, basic);
    }
}

void models_selections(devices_info *dev_info, models mod)
{
    switch (mod)
    {
    case ux581l:
        ux581l_mode(dev_info);
        break;

    case basic:
        basic_mode(dev_info);
        break;
    default:
        error("Unable to recognize targets model.", dev_info);
    }
}

void ux581l_mode(devices_info *dev_info)
{
    keymap_init(dev_info, 4, 5, 0.3f);

    unsigned short code = KEY_9;
    for (short line = 0; line <= 2; line++)
        for (short col = 2; col >= 0; col--)
        {
            keymap_set(dev_info, line, col, (key){1, code});
            code--;
        }

    keymap_set(dev_info, 0, 3, (key){1, KEY_DOT});
    keymap_set(dev_info, 0, 4, (key){0, KEY_BACKSPACE});
    keymap_set(dev_info, 1, 3, (key){0, KEY_BACKSLASH});
    keymap_set(dev_info, 1, 4, (key){0, KEY_BACKSPACE});
    keymap_set(dev_info, 2, 3, (key){0, KEY_6});
    keymap_set(dev_info, 2, 4, (key){1, KEY_APOSTROPHE});
    keymap_set(dev_info, 3, 0, (key){1, KEY_0});
    keymap_set(dev_info, 3, 1, (key){1, KEY_COMMA});
    keymap_set(dev_info, 3, 2, (key){0, KEY_ENTER});
    keymap_set(dev_info, 3, 3, (key){1, KEY_EQUAL});
    keymap_set(dev_info, 3, 4, (key){0, KEY_EQUAL});
}

void basic_mode(devices_info *dev_info)
{
    keymap_init(dev_info, 4, 3, 0.f);

    unsigned short code = KEY_9;
    for (short line = 0; line <= 2; line++)
        for (short col = 2; col >= 0; col--)
        {
            keymap_set(dev_info, line, col, (key){1, code});
            code--;
        }

    keymap_set(dev_info, 3, 0, (key){0, KEY_RESERVED});
    keymap_set(dev_info, 3, 1, (key){1, KEY_0});
    keymap_set(dev_info, 3, 2, (key){0, KEY_RESERVED});
}
