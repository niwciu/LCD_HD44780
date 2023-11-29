#############################################################################################################################
# file:  CMakeLists.txt
# brief: Template "CMakeLists.txt" for building of executables and static libraries.
#
# usage: Edit MCPU-Variable to suit STM32 project requirements.
#        For debug build using Unix Makefiles:
#          cmake -S ./ -B Debug -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
#          make -C Debug all (optional with VERBOSE=1  and -jxx ->xx numnber of cores)
#        For debug build using Ninja:
#          cmake -S ./ -B Debug -G"Ninja" -DCMAKE_BUILD_TYPE=Debug
#          ninja -C Debug (optional with -V  and -jxx ->xx numnber of cores)
# 
#        For release build Unix Makefiles:
#          cmake -S ./ -B Release -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
#          make all -C Release VERBOSE=1 -j12 (optional with VERBOSE=1  and -jxx ->xx numnber of cores)
#        For Release build using Ninja:
#          cmake -S ./ -B Release -G"Ninja" -DCMAKE_BUILD_TYPE=Release
#          ninja -C Release (optional -V  and -jxx ->xx numnber of cores)
#############################################################################################################################
cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE ../config/STM32/Toolchain-arm-gcc.cmake)

# Allow assembler
enable_language(ASM)

project(STM32F091RB_TEMPLATE)

set(INCLUDE_DIRS
Core
Core/Inc
Core/Startup

Drivers
Drivers/CMSIS
Drivers/CMSIS/Device
Drivers/CMSIS/Include
Drivers/CMSIS/STM32F0_Drivers


../src

../lib

.
)

set(C_SRCS
    Core/Src/main.c
    Core/Src/syscalls.c
    Core/Src/sysmem.c
    Core/Src/core_init.c
    Core/Src/system_stm32f0xx.c

	
)

set(ASM_SRCS
    Core/Startup/startup_stm32f091rbtx.s
)

set(GLOBAL_DEFINES
    -DSTM32F091xC
)

set(LINKED_LIBS

)

link_directories(

)

include_directories(${INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

set(MCPU "-mcpu=cortex-m0")
include(    ../config/STM32/compiler_flags.cmake)

# generate elf file
add_arm_executable(${CMAKE_PROJECT_NAME} ${C_SRCS} ${ASM_SRCS})

arm_link_libraries(${CMAKE_PROJECT_NAME} ${LINKED_LIBS})
