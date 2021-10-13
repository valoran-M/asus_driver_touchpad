#ifndef MODELS_H
#define MODELS_H

#include "defines.h"

typedef enum
{
    ux581l
} models;

/**
 * map keys with model in info
 * 
 * @param models model
 * 
 **/
void key_init(devices_info *dev_info, models mod);

/**
 * init ux581l model
 * 
 * @return key**
 * 
 **/
key **mod1_init();

/**
 * init key[][] array
 * 
 * @param int line
 * @param int colonne
 * 
 * @return key**
 * 
 **/
key **tab_init(int line, int colonne);

#endif // MODELS_H