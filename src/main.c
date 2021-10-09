#include "utility/uinput_init.h"
#include "utility/utility.h"
#include "models/models.h"
#include "event/run.h"
#include "utility/get_proc.h"

int main(int argc, char const *argv[])
{
    devices_info dev_info;
    get_devices(&dev_info);
    max_min(&dev_info);
    init_models(&dev_info, argc, argv);
    setup_uinput(&dev_info);

    run(&dev_info);

    stop(&dev_info);
    return 0;
}
