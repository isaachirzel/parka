cmake_minimum_required(VERSION 3.14)
project("Grackle")

# main executable
file(GLOB_RECURSE SRCS "src/*.c")
add_executable(grackle ${SRCS})

# setting c standard
set_target_properties(grackle PROPERTIES C_STANDARD 17)

# include folders
target_include_directories(grackle PRIVATE "include" "lib/c-utils/include")

# adding definition for asserts
add_compile_definitions(DEBUG_MODE)

# getting rid of deprecation warnings on windows
if (WIN32)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# symlink for test files
file(CREATE_LINK "..\\test" "test" SYMBOLIC)
