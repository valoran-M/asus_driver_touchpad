#include <stdio.h>

#include "utility/utility.h"
#include "models/models.h"
#include "event/run.h"

int main(int argc, char const *argv[])
{
    devices_info *info = get_devices();
    max_min(info);
    init_models(info, argc, argv);

    run(info);

    stop(info);
    return 0;
}
