project(hw_1 C)

add_executable(hw_1 read.c func.c)
add_executable(hw_1_tests tests.c func.c)

add_custom_target(check_hw_1
    COMMAND hw_1_tests
    DEPENDS hw_1_tests
)