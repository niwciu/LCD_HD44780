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

set(CMAKE_TOOLCHAIN_FILE ../config/AVR/Toolchain-AVR-gcc.cmake)

# Allow assembler
enable_language(ASM)

project(AVR_ATMEGA328P_TEMPLATE)

## AVR Chip Configuration
# Set the CPU Freq coresponding with fusebit settings
set(F_CPU 16000000UL)
# CPU definition, you can find the list here:
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MMCU atmega328p)

# Default Baudrate for UART, read avr include/util/setbaud.h for usage
# set(BAUD 9600)

# The programmer to use, read avrdude manual for list
set(PROG_TYPE usbasp)

# AVR Fuses, must be in concordance with your hardware and F_CPU
# http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega328p
set(E_FUSE 0xfd)
set(H_FUSE 0xda)
set(L_FUSE 0xfd)
set(LOCK_BIT 0xff)

set(INCLUDE_DIRS
	./inc	
)

set(C_SRCS
	./src/main.c
	./src/debug.c
)

set(ASM_SRCS

)

set(GLOBAL_DEFINES
-DF_CPU=${F_CPU}
# -DBAUD=${BAUD}
)

set(LINKED_LIBS

)



link_directories(

)

include_directories(${INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

include(    ../config/AVR/AVR_compiler_flags.cmake)
add_compile_options(${COMPILE_OPTIONS})
# generate elf file
add_AVR_executable(${CMAKE_PROJECT_NAME} ${C_SRCS} ${ASM_SRCS})

AVR_link_libraries(${CMAKE_PROJECT_NAME} ${LINKED_LIBS})