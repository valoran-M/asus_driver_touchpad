#include <string.h>
#include <stdio.h>

#include <linux/input-event-codes.h>

#include "models.h"
#include "utility/utility.h"
#include "models/models_type.h"

void init_models(devices_info *dev_info, int argc, char const *args[])
{
    enum models code = ux581l;
    dev_info->line = 4;
    dev_info->colonne = 5;
    key_init(dev_info, code);
}