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
#         	3. ninja -C out -o lcd_hd44780.o (optional with -V  and -jxx ->xx numnber of cores)
# additional custom targets for this project:
# 		Running unit tests when you are in out folder:
# 			1. make run
# 		If lizard is installed and you are in the out folder:
# 			1. make ccm -> code complexity metrix print in console
# 			2. make ccmr -> code complexity metrics report generation
# 		If cppcheck is installed and you are in the out folder
# 			1. make cppcheck_src -> static analize  for src folder printed in console
# 			2. make cppcheck_test-> static analize  for src folder printed in console
# 		If gcovr is installed and you are in the out folder
# 			1. make ccr -> code coverage report generation 
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
	# -DAVR
)

include(${CUSTOM_TARGETS_FILE_DIR})

include_directories(${INCLUDE_DIRS} ${TEST_INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

link_libraries(unity)
add_executable(${PROJECT_NAME} ${SRCS} ${TEST_SRCS})

target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
target_link_options(${PROJECT_NAME} PRIVATE -fprofile-arcs)