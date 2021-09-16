cmake_minimum_required(VERSION 3.0)

project(asus_driver_touchpad VERSION 0.0.1)

set(SRCS
    src/init/init.c
    src/init/get_proc.c
)

set(HEADERS
    src/init/init.h
)

set(LIBS
)

add_executable(asus_driver_touchpad src/main.c ${SRCS} ${HEADERS})
target_compile_features(asus_driver_touchpad PRIVATE cxx_std_17)
target_include_directories(asus_driver_touchpad PUBLIC src/)
target_link_libraries(asus_driver_touchpad ${LIBS})
