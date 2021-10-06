#include <linux/input-event-codes.h>

#include "utility/utility.h"
#include "models/models_type.h"

void key_init(enum models mod)
{
    switch (mod)
    {
    case ux581l:
        info->keys = mod1_init();
        break;

    default:
        info->keys = mod1_init();
        break;
    }
}

key **mod1_init()
{
    key **keys = tab_init(4, 5);
    int code = KEY_9;
    for (int line = 0; line <= 2; line++)
        for (int col = 2; col >= 0; col--)
        {
            keys[line][col] = (key){0, code};
            code--;
        }
    keys[0][3] = (key){0, KEY_BACKSLASH};
    keys[0][4] = (key){0, KEY_BACKSPACE};
    keys[1][3] = (key){1, KEY_BACKSLASH};
    keys[1][4] = (key){0, KEY_BACKSPACE};
    keys[2][3] = (key){0, KEY_MINUS};
    keys[2][4] = (key){0, KEY_APOSTROPHE};
    keys[3][0] = (key){0, KEY_0};
    keys[3][1] = (key){0, KEY_DOT};
    keys[3][2] = (key){0, KEY_ENTER};
    keys[3][3] = (key){1, KEY_EQUAL};
    keys[3][4] = (key){0, KEY_EQUAL};

    return keys;
}

key **tab_init(int line, int colonne)
{
    key **keys = calloc(line, sizeof(key *));
    for (unsigned int i = 0; i < line; i++)
    {
        keys[i] = calloc(colonne, sizeof(key));
    }
    return keys;
}
