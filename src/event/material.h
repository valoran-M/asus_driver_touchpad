#ifndef MATERIAL_H
#define MATERIAL_H

static int brightness = 0;

static char *bright[] = {"0x1f", "0x18", "0x01"};

void activate_numpad();

void desactivate_numpad();

void change_brightness();

void turn_on_touchpad();

void turn_off_touchpad();

#endif