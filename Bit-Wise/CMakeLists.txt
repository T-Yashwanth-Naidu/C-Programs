# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(Bit-Wise-Problems)

# Set the C standard (if needed)
set(CMAKE_C_STANDARD 99)

# Add executable target and source files
add_executable(a.out
    main_file.c
    check_even_odd.c
    check_opposite_signs.c
    swap_integers.c
    set_unset_kth_bit.c
    find_set_bits.c
    printBinary.c
    functions.h   
    libs.h
)

# Optionally, include directories (if your headers are in a separate directory)
include_directories(${CMAKE_SOURCE_DIR})

# Link libraries (if you have external libraries)
# target_link_libraries(MyExecutable <library_name>)
