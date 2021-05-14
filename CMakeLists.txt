cmake_minimum_required(VERSION 3.0)
project("Grackle")

# main executable
file(GLOB SRCS "src/*.c")
add_executable(grackle ${SRCS})
target_include_directories(grackle PRIVATE "include" "lib/c-utils/include")

# symlink for test files
file(CREATE_LINK ../test test SYMBOLIC)
