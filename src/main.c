#include "init/init.h"



int main(int argc, char const *argv[])
{
    devices_info *info = get_devices();

    printf("%d, %d, %d\n", info->file_keyboard, info->file_touchpad, info->i2c);
    
    stop(info);
    return 0;
}
