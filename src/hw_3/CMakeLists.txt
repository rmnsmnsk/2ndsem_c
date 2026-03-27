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