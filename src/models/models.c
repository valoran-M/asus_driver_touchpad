#include <string.h>
#include <stdio.h>

#include <linux/input-event-codes.h>

#include "models.h"
#include "utility/utility.h"
#include "models/models_type.h"

void init_models(int argc, char const *args[])
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
    key_init(code);
}