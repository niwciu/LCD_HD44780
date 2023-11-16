cmake_minimum_required(VERSION 3.10)

project(template_test C)

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
	#../../src/tested_module_folder/tested_module.c
)

set(TEST_SRCS
    template_test_main.c
    template_test_runner.c
    template_test.c
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