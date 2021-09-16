#include "init/init.h"


int main(int argc, char const *argv[])
{
    devices_info *info = get_devices();
    
    free(info);
    return 0;
}
