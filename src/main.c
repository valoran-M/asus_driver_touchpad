#include "utility/utility.h"
#include "models/models.h"
#include "event/run.h"

int main(int argc, char const *argv[])
{
    devices_info *info = get_devices();
    max_min(info);

    run(info);

    stop(info);
    return 0;
}
