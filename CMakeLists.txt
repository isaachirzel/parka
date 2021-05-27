cmake_minimum_required(VERSION 3.14)
project("Grackle")

# main executable
file(GLOB_RECURSE SRCS "src/*.c")
add_executable(grackle ${SRCS})
target_include_directories(grackle PRIVATE "include" "lib/c-utils/include")
add_compile_definitions(DEBUG_MODE)

# symlink for test files
file(CREATE_LINK ../test test SYMBOLIC)
