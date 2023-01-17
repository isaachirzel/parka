cmake_minimum_required(VERSION 3.0)
project("warbler")

set(MAIN_PROGRAM "warble")
set(INCLUDE_DIRS "include")

if (MSVC)
	add_compile_options(/W4)
else()
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		add_compile_options(-fdiagnostics-color=always -fanalyzer)
	endif()
	add_compile_options(-pedantic -Wall -Wextra -Wreturn-type -O0)
	# add_compile_options(-Werror)
endif()

if (WIN32)
	# getting rid of deprecation warnings on windows
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

file(GLOB_RECURSE COMMON_SOURCES "src/warbler/*.c")
add_library(common OBJECT ${COMMON_SOURCES})
add_executable(warble "src/main.c" $<TARGET_OBJECTS:common>)
list(APPEND TARGETS ${MAIN_PROGRAM} common)

# creating targets for all test sources
file(GLOB TEST_SOURCES "src/test/*.c")
foreach(TEST ${TEST_SOURCES})
	get_filename_component(TEST_TARGET_NAME ${TEST} NAME_WE)
	add_executable(${TEST_TARGET_NAME} ${TEST} $<TARGET_OBJECTS:common>)
	list(APPEND TARGETS ${TEST_TARGET_NAME})
endforeach()

# adding common properties for all targets
foreach(TARGET ${TARGETS})
	set_target_properties(${TARGET} PROPERTIES C_STANDARD 17)
	target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRS})
endforeach()
