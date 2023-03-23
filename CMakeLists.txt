cmake_minimum_required(VERSION 3.0)
project("parka")

set(MAIN_PROGRAM "parka")
set(INCLUDE_DIRS "include")

message("Source dir: ${SRC}")
set(SRC ".")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# if (MSVC)
# 	add_compile_options(/W4)
# else()
# 	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
# 		add_compile_options(-fdiagnostics-color=always -fanalyzer)
# 	endif()
# 	add_compile_options(-std=c++17 -pedantic -Wall -Wextra -Wreturn-type -O0)
# 	add_compile_options(-Werror)
# endif()

# if (WIN32)
# 	# getting rid of deprecation warnings on windows
# 	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
# endif()

file(GLOB_RECURSE COMMON_SOURCES "src/parka/*.cpp")
add_library(common OBJECT ${COMMON_SOURCES})
add_executable(parka "src/main.cpp" $<TARGET_OBJECTS:common>)
list(APPEND TARGETS ${MAIN_PROGRAM} common)

# creating targets for all test sources
file(GLOB TEST_SOURCES "src/test/*.cpp")
foreach(TEST ${TEST_SOURCES})
	get_filename_component(TEST_TARGET_NAME ${TEST} NAME_WE)
	add_executable(${TEST_TARGET_NAME} ${TEST} $<TARGET_OBJECTS:common>)
	list(APPEND TARGETS ${TEST_TARGET_NAME})
endforeach()

# adding common properties for all targets
foreach(TARGET ${TARGETS})
	target_compile_features(${TARGET} PRIVATE cxx_std_17)
	set_target_properties(${TARGET} PROPERTIES CXX_STANDARD 17)
	target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRS})
endforeach()
