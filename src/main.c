#include <stdio.h>

#include "utility/uinput_init.h"
#include "utility/utility.h"
#include "models/models.h"
#include "event/run.h"

int main(int argc, char const *argv[])
{
    devices_info *info = get_devices();
    max_min(info);
    init_models(info, argc, argv);

    setup_uinput(info);

    run(info);

    stop(info);
    return 0;
}
