#include "init/init.h"



int main(int argc, char const *argv[])
{
    devices_info *info = get_devices();

    stop(info);
    return 0;
}
