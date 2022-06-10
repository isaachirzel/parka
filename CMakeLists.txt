cmake_minimum_required(VERSION 3.0)
project("warbler")

set(MAIN_PROGRAM "warble")
set(INCLUDE_DIRS "include")

if (MSVC)
	add_compile_options(/W4)
else()
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		add_compile_options(-fdiagnostics-color=always)
	endif()
	add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Wstrict-aliasing -fmax-errors=5 -Wunreachable-code -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option)
endif()

if (WIN32)
	# getting rid of deprecation warnings on windows
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# adding definition for asserts
add_compile_definitions(DEBUG_MODE)

file(GLOB_RECURSE COMMON_SOURCES "src/warbler/*.cpp")
add_library(common_objects OBJECT ${COMMON_SOURCES})
add_executable(warble "src/main.cpp" $<TARGET_OBJECTS:common_objects>)
list(APPEND TARGETS ${MAIN_PROGRAM} common_objects)

# creating targets for all test sources
file(GLOB TEST_SOURCES "src/test/*.cpp")
foreach(TEST ${TEST_SOURCES})
	get_filename_component(TEST_TARGET_NAME ${TEST} NAME_WE)
	add_executable(${TEST_TARGET_NAME} ${TEST} $<TARGET_OBJECTS:common_objects>)
	list(APPEND TARGETS ${TEST_TARGET_NAME})
endforeach()

# adding common properties for all targets
foreach(TARGET ${TARGETS})
	set_target_properties(${TARGET} PROPERTIES C_STANDARD 11 CXX_STANDARD 17)
	target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRS})
endforeach()
