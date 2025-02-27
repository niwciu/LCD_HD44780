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

project(STM32G474RE_NUCLEO_CUBE_IDE_LCD_TEST)

set(INCLUDE_DIRS
../
./Core
./Core/Inc
.
)

set(C_SRCS
    Core/Src/main.c
    Core/Src/stm32g4xx_it.c
    Core/Src/syscalls.c
    Core/Src/sysmem.c
    Core/Src/system_stm32g4xx.c
    Core/Src/LCD_IO_driver.c
    Core/Src/tim_delay.c

    # Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_dma.c
    # Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_exti.c
    # Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_gpio.c
    # Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_lpuart.c
    # Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_pwr.c
    # Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_rcc.c
    # # Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_tim.c
    # Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_utils.c
	
)

set(ASM_SRCS
    Core/Startup/startup_stm32g474retx.s
)

set(GLOBAL_DEFINES
-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
-DSTM32G474xx 
-DUSE_FULL_LL_DRIVER 
-DHSE_VALUE=24000000 
-DHSE_STARTUP_TIMEOUT=100 
-DLSE_STARTUP_TIMEOUT=5000 
-DLSE_VALUE=32768 
-DEXTERNAL_CLOCK_VALUE=12288000 
-DHSI_VALUE=16000000 
-DLSI_VALUE=32000 
-DVDD_VALUE=3300 
-DPREFETCH_ENABLE=0 
-DINSTRUCTION_CACHE_ENABLE=1 
-DDATA_CACHE_ENABLE=1 
)

set(LINKED_LIBS
  lib_lcd_hd44780
  lib_hal_ll_drivers
)
set(MCPU "-mcpu=cortex-m4")
include(    ../config/STM32/compiler_flags.cmake)


include_directories(${INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

add_subdirectory(../../src lib_lcd_hd44780)
add_subdirectory(./Drivers lib_hal_ll_drivers)
link_directories(
  
)

# generate elf file
add_arm_executable(${CMAKE_PROJECT_NAME} ${C_SRCS} ${ASM_SRCS})

arm_link_libraries(${CMAKE_PROJECT_NAME} ${LINKED_LIBS})
