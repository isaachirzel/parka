cmake_minimum_required(VERSION 3.0)
project("warbler")

# common objects
set(INCLUDE_DIRS
	"include"
)

set(MAIN_PROGRAM
	"warble"
)

file(GLOB_RECURSE COMMON_SOURCES "src/warbler/*.c")
add_library(common_objects OBJECT ${COMMON_SOURCES})
add_executable(warble "src/main.c" $<TARGET_OBJECTS:common_objects>)
list(APPEND TARGETS ${MAIN_PROGRAM} common_objects)

# adding definition for asserts
add_compile_definitions(DEBUG_MODE)

if (WIN32)
	# getting rid of deprecation warnings on windows
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

if (MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -pedantic)
endif()

# creating targets for all test sources
file(GLOB TEST_SOURCES "src/test/*.c")
foreach(TEST ${TEST_SOURCES})
	get_filename_component(TEST_TARGET_NAME ${TEST} NAME_WE)
	add_executable(${TEST_TARGET_NAME} ${TEST} $<TARGET_OBJECTS:common_objects>)
	list(APPEND TARGETS ${TEST_TARGET_NAME})
endforeach()

# adding common properties for all targets
foreach(TARGET ${TARGETS})
	set_target_properties(${TARGET} PROPERTIES C_STANDARD 99)
	target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRS})
endforeach()
