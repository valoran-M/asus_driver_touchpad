cmake_minimum_required(VERSION 3.0)

project(asus_driver_touchpad VERSION 0.0.1)

set(SRCS
        src/events/event_loop.c
        src/events/interface.c
        src/events/keys_events.c
        src/kernel_setup/models.c
        src/kernel_setup/device.c
        src/kernel_setup/uinput.c
        src/utils/utils.c
        src/utils/keymap.c
        )

set(HEADERS
        src/events/keys_events.h
        src/events/interface.h
        src/events/keys_events.h
        src/kernel_setup/models.h
        src/kernel_setup/device.h
        src/defines.h
        src/kernel_setup/uinput.h
        src/utils/utils.h
        src/utils/keymap.h
        )

add_executable(asus_driver_touchpad src/main.c ${SRCS} ${HEADERS})
target_compile_features(asus_driver_touchpad PRIVATE cxx_std_17)
target_include_directories(asus_driver_touchpad PUBLIC src/)
target_link_libraries(asus_driver_touchpad PUBLIC m)
