cmake_minimum_required(VERSION 3.10)
project(CityDistributor)

set(CMAKE_C_STANDARD 99)

add_executable(city_distributor
    main.c
    func.c
)

add_executable(tests
    tests.c
    func.c
)

add_custom_target(check_hw_3
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests
    DEPENDS tests
)