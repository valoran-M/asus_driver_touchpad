#ifndef MODELS_TYPE
#define MODELS_TYPE

#include "utility/utility.h"

enum models
{
    ux581l
};

key **key_init(enum models mod);

key **mod1_init();

key **tab_init(int line, int colonne);

#endif