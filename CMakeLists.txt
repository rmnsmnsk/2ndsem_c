cmake_minimum_required(VERSION 3.10)
project(Taks)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/hw_1)
#add_subdirectory(src/hw_1)
#endif()

#if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/hw_2)
 #   add_subdirectory(src/hw_2)
#endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/hw_3)
    add_subdirectory(src/hw_3)
endif()