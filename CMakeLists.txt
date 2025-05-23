cmake_minimum_required(VERSION 3.16)
project("parka")

set(MAIN_PROGRAM "parka")
set(INCLUDE_DIRS "include")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
	add_compile_options(/W4)
else()
	if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
		add_compile_options(-fdiagnostics-color=always)
	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		add_compile_options(-fcolor-diagnostics -fansi-escape-codes)
	endif()

	add_compile_options(-pedantic -Wall -Wextra) #-Wno-error=unused-parameter -Wno-error=unused-variable -Wno-error=class-memaccess
	add_compile_options(-Werror=return-type)
endif()

if (WIN32)
	# getting rid of deprecation warnings on windows
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

file(GLOB_RECURSE COMMON_SOURCES "src/parka/*.cpp")
add_library(common OBJECT ${COMMON_SOURCES})
add_executable(parka "src/parka.cpp" $<TARGET_OBJECTS:common>)
list(APPEND TARGETS ${MAIN_PROGRAM} common)

# creating targets for all test sources
file(GLOB TEST_SOURCES "tests/*.cpp")
foreach(TEST ${TEST_SOURCES})
	get_filename_component(TEST_FILE_NAME ${TEST} NAME_WE)
	set(TEST_TARGET_NAME "test_${TEST_FILE_NAME}")
	add_executable(${TEST_TARGET_NAME} ${TEST} $<TARGET_OBJECTS:common>)
	list(APPEND TARGETS ${TEST_TARGET_NAME})
endforeach()

# adding common properties for all targets
foreach(TARGET ${TARGETS})
	target_compile_features(${TARGET} PRIVATE cxx_std_17)
	set_target_properties(${TARGET} PROPERTIES CXX_STANDARD 17)
	target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRS})
	target_precompile_headers(${TARGET} PRIVATE
		"<stdexcept>"
		"<exception>"
		"<utility>"
		"<ostream>"
		"<cassert>"
		"<type_traits>"
		"<cstdlib>"
		"<cstddef>"
		"<chrono>"
		"<filesystem>"
		"<new>"
		"<memory>"
		"<string>"
		"<vector>"
	)
endforeach()
