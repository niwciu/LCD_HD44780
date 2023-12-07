cmake_minimum_required(VERSION 3.10)

project(lcd_hd44780_test C)

add_subdirectory(../unity unity)

set(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

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
	#mock_module.c
)

set(GLOBAL_DEFINES

)

include_directories(${INCLUDE_DIRS} ${TEST_INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

link_libraries(unity)
add_executable(${PROJECT_NAME} ${SRCS} ${TEST_SRCS})

target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
target_link_options(${PROJECT_NAME} PRIVATE -fprofile-arcs)