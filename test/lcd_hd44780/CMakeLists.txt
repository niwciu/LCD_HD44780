#############################################################################################################################
# file:  CMakeLists.txt
# brief: Template "CMakeLists.txt" for building Unit test modules.
#
# usage:
#        For build using Unix Makefiles:
#          	1.cmake -S./ -B out -G"Unix Makefiles"
#			2.enter the "out" folder
#          	3.make all -o lcd_hd44780.o (-jXX additionaly to speed up)
#        For build using Ninja:
#          	1. cmake -S./ -B out -G"Ninja"
# 			2. enter the "out" folder
#         	3. ninja -C out -o lcd_hd44780.o (optional with -V )
# 
#############################################################################################################################
cmake_minimum_required(VERSION 3.10)

project(lcd_hd44780_test C)

add_subdirectory(../unity unity)

set(CUSTOM_TARGETS_FILE_DIR ./custom_targets.cmake)

set(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
endif()

set(INCLUDE_DIRS
	../../src
)

set(TEST_INCLUDE_DIRS
	..
	.
)

set(SRCS
	../../src/lcd_hd44780.c
)

set(TEST_SRCS
	lcd_hd44780_test_main.c
	lcd_hd44780_test_runner.c
	lcd_hd44780_test_init.c
	mock_LCD_IO_driver.c
	lcd_hd44780_test_basic_func.c
	lcd_hd44780_test_common.c
	lcd_hd44780_test_buffering.c
	#mock_module.c
)

set(GLOBAL_DEFINES
	-DUNIT_TEST
)
# set -g3 flag for enabling debug on developing maching
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3")
include(${CUSTOM_TARGETS_FILE_DIR})

include_directories(${INCLUDE_DIRS} ${TEST_INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

link_libraries(unity)
add_executable(${PROJECT_NAME} ${SRCS} ${TEST_SRCS})

target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
target_link_options(${PROJECT_NAME} PRIVATE -fprofile-arcs)