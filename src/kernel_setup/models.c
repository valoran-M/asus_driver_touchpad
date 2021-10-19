#include <linux/input-event-codes.h>

#include "models.h"
#include <stdlib.h>

void init_models(devices_info *dev_info, int argc, char const *args[])
{
    keymap_init(dev_info, ux581l);
}

void keymap_init(devices_info *dev_info, models mod)
{
    switch (mod) {
        case ux581l:
            ux581l_mode(dev_info);
            break;

        case basic:
            basic_mode(dev_info);
            break;
        default:
            error("Unable to recognize targets model.");
    }
}

key **array_init(unsigned short line, unsigned short colonne)
{
    key **keys = calloc(line, sizeof(key *));
    if (keys == NULL) {
        error("Bad alloc (keys@array_init).\n");
    }

    for (unsigned int i = 0; i < line; i++) {
        keys[i] = calloc(colonne, sizeof(key));

        if (keys[i] == NULL) {
            for (unsigned int j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            error("Bad alloc (*keys@array_init).\n");
        }
    }

    return keys;
}

void ux581l_mode(devices_info *dev_info)
{
    dev_info->line = 4;
    dev_info->colonne = 5;
    dev_info->keys = array_init(dev_info->line, dev_info->colonne);

    unsigned short code = KEY_9;
    for (int line = 0; line <= 2; line++) {
        for (int col = 2; col >= 0; col--) {
            dev_info->keys[line][col] = (key) {1, code};
            code--;
        }
    }

    dev_info->keys[0][3] = (key) {1, KEY_DOT};
    dev_info->keys[0][4] = (key) {0, KEY_BACKSPACE};
    dev_info->keys[1][3] = (key) {0, KEY_BACKSLASH};
    dev_info->keys[1][4] = (key) {0, KEY_BACKSPACE};
    dev_info->keys[2][3] = (key) {0, KEY_6};
    dev_info->keys[2][4] = (key) {1, KEY_APOSTROPHE};
    dev_info->keys[3][0] = (key) {1, KEY_0};
    dev_info->keys[3][1] = (key) {1, KEY_COMMA};
    dev_info->keys[3][2] = (key) {0, KEY_ENTER};
    dev_info->keys[3][3] = (key) {1, KEY_EQUAL};
    dev_info->keys[3][4] = (key) {0, KEY_EQUAL};
}

void basic_mode(devices_info *dev_info)
{
    dev_info->line = 4;
    dev_info->colonne = 3;
    dev_info->keys = array_init(dev_info->line, dev_info->colonne);

    unsigned short code = KEY_9;
    for (int line = 0; line <= 2; line++) {
        for (int col = 2; col >= 0; col--) {
            dev_info->keys[line][col] = (key) {1, code};
            code--;
        }
    }

    dev_info->keys[3][0] = (key) {1, KEY_RESERVED};
    dev_info->keys[3][1] = (key) {1, KEY_0};
    dev_info->keys[3][2] = (key) {1, KEY_RESERVED};
}
