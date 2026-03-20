cmake_minimum_required(VERSION 3.10)
project(AeroSoft)

set(CMAKE_C_STANDARD 11)

add_executable(aerosoft main.c avl-tree.c)

add_executable(test_avl avl-test.c avl-tree.c)