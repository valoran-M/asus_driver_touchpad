#include "keymap.h"

#include <stdlib.h>

void keymap_init(devices_info *dev_info, unsigned short line, unsigned short colonne)
{
    dev_info->mapping.line = line;
    dev_info->mapping.colonne = colonne;
    dev_info->mapping.keys = calloc(line * colonne, sizeof(key));

    if (dev_info->mapping.keys == NULL) {
        error("Bad alloc (keys@models_selections).\n");
    }
}

void keymap_free(devices_info *dev_info)
{
    if (dev_info->mapping.keys == NULL) {
        error("Bad address provided.\n");
    }

    free(dev_info->mapping.keys);
}

void keymap_set(devices_info *dev_info, unsigned short line, unsigned short colonne, key k)
{
    if (line * colonne > dev_info->mapping.line * dev_info->mapping.colonne) {
        error("Address out of range.\n");
    }

    dev_info->mapping.keys[dev_info->mapping.colonne * line + colonne] = k;
}

key keymap_get(devices_info *dev_info, unsigned short line, unsigned short colonne)
{
    if (line * colonne > dev_info->mapping.line * dev_info->mapping.colonne) {
        error("Address out of range.\n");
    }

    return dev_info->mapping.keys[dev_info->mapping.colonne * line + colonne];
}
