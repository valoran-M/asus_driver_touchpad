cmake_minimum_required(VERSION 3.0)

project(asus_driver_touchpad VERSION 0.0.1)

set(SRCS
    
)

set(HEADERS

)

set(TESTS

)

add_executable(asus_driver_touchpad src/main.c ${SRCS} ${HEADERS})
target_compile_features(asus_driver_touchpad PRIVATE cxx_std_17)
target_include_directories(asus_driver_touchpad PUBLIC src/)
