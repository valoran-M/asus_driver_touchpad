#include <linux/input-event-codes.h>

#include "utility/utility.h"
#include "models/models_type.h"

key **key_init(enum models mod)
{
    key **keys;
    switch (mod)
    {
    case ux581l:
        keys = mod1_init();
        break;

    default:
        keys = mod1_init();
        break;
    }
    return keys;
}

key **mod1_init()
{
    key **keys = tab_init(4, 5);
    int code = KEY_9;
    for (int line = 0; line <= 2; line++)
        for (int col = 2; col >= 0; col--)
        {
            keys[line][col] = (key){0, code};
            printf("%d, %d -> %d\n", line, col, code);
            code--;
        }
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
