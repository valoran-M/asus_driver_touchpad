#include "error.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

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

//void info(const char *output, const void *data)
//{
//    size_t str_size = strlen(output) + 100;
//    char *buffer = malloc(str_size);
//
//    if (buffer == NULL) {
//        error("Bad alloc (buffer@info).\n");
//    }
//
//    snprintf(buffer, str_size, output, data);
//    printf("[INFO] : %s", buffer);
//
//    free(buffer);
//}
//
//void safe_ioctl(int fd, unsigned long int request, void *data)
//{
//    if (ioctl(fd, request, data) == -1) {
//        error("ioctl() call failed.");
//    }
//
//}

void check_ioctl(int return_code)
{
    if (return_code == -1) {
        error("ioctl() call failed.");
    }
}