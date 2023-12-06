# System Generic - no OS bare-metal application
set(CMAKE_SYSTEM_NAME Generic)

# Setup arm processor and bleeding edge toolchain
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_NM arm-none-eabi-nm)
set(CMAKE_STRIP arm-none-eabi-strip)
set(CMAKE_RANLIB arm-none-eabi-ranlib)
set(CMAKE_SIZE arm-none-eabi-size)

# When trying to link cross compiled test program, error occurs, so setting test compilation to static library
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Don't know if following setting works also for Ninja
set(CMAKE_VERBOSE_MAKEFILE OFF)

# Remove default static libraries for win32
set(CMAKE_C_STANDARD_LIBRARIES "")

macro(add_arm_executable target_name)

# Output files
set(elf_file ${target_name}.elf)
set(map_file ${target_name}.map)
set(hex_file ${target_name}.hex)
set(bin_file ${target_name}.bin)
set(lss_file ${target_name}.lss)
set(dmp_file ${target_name}.dmp)

add_executable(${elf_file} ${ARGN})

#generate hex file
add_custom_command(
	OUTPUT ${hex_file}

	COMMAND
		${CMAKE_OBJCOPY} -O ihex ${elf_file} ${hex_file}

	DEPENDS ${elf_file}
)

# #generate bin file
add_custom_command(
	OUTPUT ${bin_file}

	COMMAND
		${CMAKE_OBJCOPY} -O binary ${elf_file} ${bin_file}

	DEPENDS ${elf_file}
)

# #generate extended listing
add_custom_command(
	OUTPUT ${lss_file}

	COMMAND
		${CMAKE_OBJDUMP} -h -S ${elf_file} > ${lss_file}

	DEPENDS ${elf_file}
)

# #generate memory dump
add_custom_command(
	OUTPUT ${dmp_file}

	COMMAND
		${CMAKE_OBJDUMP} -x --syms ${elf_file} > ${dmp_file}

	DEPENDS ${elf_file}
)




#postprocessing from elf file - generate hex bin etc.
add_custom_target(
	${CMAKE_PROJECT_NAME}
	ALL
	DEPENDS ${hex_file} ${bin_file} ${lss_file} ${dmp_file}
)

set_target_properties(
	${CMAKE_PROJECT_NAME}

	PROPERTIES
		OUTPUT_NAME ${elf_file}
)
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD 
	COMMAND ${CMAKE_SIZE} --format=berkeley ${elf_file} ${hex_file})
# check if programmer software is available 
find_program(STM32_Programmer STM32_Programmer_CLI)
if(STM32_Programmer)
	message(STATUS "STM32 Programmer was found, you can work with your device using targets: \r\n\t flash,\r\n\t erase,\r\n\t reset.")	
else()
	message(STATUS "STM32 Programmer was not found.")  
endif()
# add "flash" command for programming the uC
add_custom_target(flash COMMAND ${STM32_Programmer} --connect port=SWD --write $<TARGET_FILE:${elf_file}> --verify -rst)
add_custom_target(erase COMMAND ${STM32_Programmer} -c port=SWD -e all)
add_custom_target(reset COMMAND ${STM32_Programmer} -c port=SWD -rst)

endmacro(add_arm_executable)

macro(arm_link_libraries target_name)

target_link_libraries(${target_name}.elf ${ARGN})

endmacro(arm_link_libraries)
