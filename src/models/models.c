#include <string.h>
#include <stdio.h>

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

void init_models(devices_info *info, int argc, int *args[])
{
    if (argc > 1)
    {
        info->line = 4;
        info->colonne = 5;
        info->keys = keys_init(info->line, info->colonne);
    }
    else
    {
        info->line = 4;
        info->colonne = 5;
        info->keys = keys_init(info->line, info->colonne);
    }
}