#include <string.h>
#include <stdio.h>

#include <linux/input-event-codes.h>

#include "models.h"
#include "utility/utility.h"
#include "models/models_type.h"

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
    enum models code = ux581l;
    info->line = 4;
    info->colonne = 5;
    if (argc > 1)
    {
        info->line = 4;
        info->colonne = 5;
        code = ux581l;
    }
    info->keys = key_init(code);
}