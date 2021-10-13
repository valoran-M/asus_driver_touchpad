#ifndef KEYMAP_H
#define KEYMAP_H

#include "defines.h"
#include "models.h"

/**
 * initialise le modèle
 * 
 * @param int argc
 * @param int** args
 * 
 **/
void init_models(devices_info *dev_info, int argc, char const *args[]);

#endif // KEYMAP_H