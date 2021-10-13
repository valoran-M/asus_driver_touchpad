#include "keymap.h"

void init_models(devices_info *dev_info, int argc, char const *args[])
{
    models code = ux581l;
    dev_info->line = 4;
    dev_info->colonne = 5;
    key_init(dev_info, code);
}