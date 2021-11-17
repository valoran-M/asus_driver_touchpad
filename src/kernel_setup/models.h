#ifndef MODELS_H
#define MODELS_H

#include "defines.h"
#include "utils/utils.h"
#include "utils/keymap.h"

typedef enum
{
    M433IA,
    UX433FA,
    basic,
} models;

/**
 * initialise le modèle
 *
 * @param int argc
 * @param int** args
 *
 **/
void init_models(devices_info *dev_info, int argc, char const *args[]);

/**
 * init key[][] array
 *
 * @param int line
 * @param int colonne
 *
 * @return key**
 *
 **/
key **array_init(unsigned short line, unsigned short colonne);

/**
 * map keys with model in info
 * 
 * @param models model
 * 
 **/
void models_selections(devices_info *dev_info, models mod);

/**
 * init M433IA model
 * 
 * @return key**
 * 
 **/
void M433IA_mode(devices_info *dev_info);

/**
 * init UX433FA model
 * 
 * @return key**
 * 
 **/
void UX433FA_mode(devices_info *dev_info);

/**
 * init basic model
 *
 * @return key**
 *
 **/
void basic_mode(devices_info *dev_info);


#endif // MODELS_H