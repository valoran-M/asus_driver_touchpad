#include "utility/uinput_init.h"
#include "utility/utility.h"
#include "models/models.h"
#include "event/run.h"

int main(int argc, char const *argv[])
{
    get_devices();
    max_min();
    init_models(argc, argv);
    setup_uinput();

    run();

    stop();
    return 0;
}
