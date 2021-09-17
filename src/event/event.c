#include <signal.h>
#include <stdio.h>

#include "event.h"

void sighandler(int sig)
{
    if (sig == SIGINT)
        loop = 0;
}