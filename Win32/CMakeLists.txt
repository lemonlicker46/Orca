cmake_minimum_required(VERSION 3.16)

project(orca_main C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Export compile_commands.json (IMPORTANT for clang-tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect all .c files
file(GLOB_RECURSE SOURCES
    src/*.c
)

# Create executable
add_executable(orca ${SOURCES})

target_link_libraries(orca PRIVATE comctl32)

target_include_directories(orca PRIVATE
    C:/MinGW/include
)

# Include headers (adjust if you have include/ folder)
target_include_directories(orca PRIVATE
    include
)

