#include <string.h>
#include <stdio.h>

#include <linux/input-event-codes.h>

#include "models.h"
#include "utility/utility.h"

key **keys_init(int line, int colonne)
{
    key **keys = calloc(line, sizeof(key *));
    for (unsigned int i = 0; i < line; i++)
    {
        keys[i] = calloc(colonne, sizeof(key));
    }
    return keys;
}

void init_models(devices_info *info, int argc, char const *args[])
{
    if (argc > 1)
    {
        info->line = 4;
        info->colonne = 5;
        info->keys = keys_init(info->line, info->colonne);
        info->keys[0][0] = (key){0, KEY_7};
    }
    else
    {
        info->line = 4;
        info->colonne = 5;
        info->keys = keys_init(info->line, info->colonne);
    }
}