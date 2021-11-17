#include "keymap.h"

#include <stdlib.h>

void keymap_init(devices_info *dev_info, unsigned short line, unsigned short colonne, float offset)
{
    dev_info->mapping.line = line;
    dev_info->mapping.colonne = colonne;
    dev_info->mapping.offset = offset;
    dev_info->mapping.keys = calloc(line * colonne, sizeof(key));

    if (dev_info->mapping.keys == NULL)
    {
        error("Bad alloc (keys@models_selections).\n", dev_info);
    }
}

void keymap_free(devices_info *dev_info)
{
    if (dev_info->mapping.keys == NULL)
    {
        warning("Trying to free a nullptr.\n");
    }

    free(dev_info->mapping.keys);
}

void keymap_set(devices_info *dev_info, unsigned short line, unsigned short colonne, key k)
{
    if (line * colonne > dev_info->mapping.line * dev_info->mapping.colonne)
    {
        error("Address out of range.\n", dev_info);
    }

    dev_info->mapping.keys[dev_info->mapping.line * colonne + line] = k;
}

key keymap_get(devices_info *dev_info, unsigned short line, unsigned short colonne)
{
    if (line * colonne > dev_info->mapping.line * dev_info->mapping.colonne)
    {
        error("Address out of range.\n", dev_info);
    }

    return dev_info->mapping.keys[dev_info->mapping.line * colonne + line];
}
