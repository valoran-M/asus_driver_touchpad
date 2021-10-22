#include "error.h"

#include <stdlib.h>
#include <stdio.h>

__attribute__((noreturn))
void error(const char *output)
{
    fprintf(stderr, "[ERROR] : %s", output);
    exit(EXIT_FAILURE);
}

void warning(const char *output)
{
    fprintf(stderr, "[WARNING] : %s", output);
}

void check_ioctl(int return_code)
{
    if (return_code == -1) {
        error("ioctl() call failed.");
    }
}
