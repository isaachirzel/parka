cmake_minimum_required(VERSION 3.0)
project("grackle")

# common objects
set(INCLUDE_DIRS "include")
file(GLOB_RECURSE COMMON_SOURCES "src/grackle/*.cpp")
add_library(common_objects OBJECT ${COMMON_SOURCES})
add_executable(${PROJECT_NAME} "src/main.cpp" $<TARGET_OBJECTS:common_objects>)
list(APPEND TARGETS ${PROJECT_NAME} common_objects)

# adding definition for asserts
add_compile_definitions(DEBUG_MODE)

if (WIN32)
	# getting rid of deprecation warnings on windows
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	file(CREATE_LINK "..\\test" "test" SYMBOLIC)
else()
	file(CREATE_LINK "../test" "test" SYMBOLIC)
endif()

# creating targets for all test sources
file(GLOB TEST_SOURCES "src/test/*.cpp")
foreach(TEST ${TEST_SOURCES})
	get_filename_component(TEST_TARGET_NAME ${TEST} NAME_WE)
	add_executable(${TEST_TARGET_NAME} ${TEST} $<TARGET_OBJECTS:common_objects>)
	list(APPEND TARGETS ${TEST_TARGET_NAME})
endforeach()

# adding common properties for all targets
foreach(TARGET ${TARGETS})
	target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRS})
	set_target_properties(${TARGET} PROPERTIES C_STANDARD 17 CXX_STANDARD 17)
endforeach()
