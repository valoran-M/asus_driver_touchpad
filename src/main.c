#include "kernel_setup/uinput.h"
#include "defines.h"
#include "kernel_setup/models.h"
#include "events/event_loop.h"
#include "kernel_setup/device.h"

int main(int argc, char const *argv[])
{
    devices_info dev_info;
    get_devices(&dev_info);
    max_min(&dev_info);
    init_models(&dev_info, argc, argv);
    setup_uinput(&dev_info);
    run(&dev_info);

    cleanup(&dev_info);
    return 0;
}
