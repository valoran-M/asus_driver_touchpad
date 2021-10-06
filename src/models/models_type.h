#ifndef MODELS_TYPE
#define MODELS_TYPE

#include "utility/utility.h"

enum models
{
    ux581l
};

/**
 * map keys with model in info
 * 
 * @param models model
 * 
 **/
void key_init(enum models mod);

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

#endif