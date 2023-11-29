# System Generic - no OS bare-metal application
set(CMAKE_SYSTEM_NAME Generic)

set(TOOLCHAIN avr)

# Setup arm processor and bleeding edge toolchain
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_C_COMPILER ${TOOLCHAIN}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN}-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN}-gcc)
set(CMAKE_AR ${TOOLCHAIN}-ar)
set(CMAKE_OBJCOPY ${TOOLCHAIN}-objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN}-objdump)
set(CMAKE_NM ${TOOLCHAIN}-nm)
set(CMAKE_STRIP ${TOOLCHAIN}-strip)
set(CMAKE_RANLIB ${TOOLCHAIN}-ranlib)
set(CMAKE_SIZE ${TOOLCHAIN}-size)

# When trying to link cross compiled test program, error occurs, so setting test compilation to static library
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Don't know if following setting works also for Ninja
set(CMAKE_VERBOSE_MAKEFILE OFF)

# Remove default static libraries for win32
set(CMAKE_C_STANDARD_LIBRARIES "")

macro(add_AVR_executable target_name)

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
add_custom_target( size ALL COMMAND ${CMAKE_SIZE} -C --mcu=${MMCU} --format=avr ${elf_file} DEPENDS ${hex_file})

# check if programmer software is available 
find_program(AVR_Programmer avrdude)
if(AVR_Programmer)
	message(STATUS "AVR_Programmer avrdude was found, you can use defined targets: \r\n\tflash,\r\n\terase,\r\n\twrite_fuse,\r\n\tread_fuse\r\n\tread_flash.")
else()
	message(STATUS "AVR_Programmer was not found.")    
endif()
# Upload the firmware with avrdude
add_custom_target(flash avrdude -c ${PROG_TYPE} -p ${MMCU} -D -U flash:w:${CMAKE_SOURCE_DIR}/build/${hex_file}:i DEPENDS size erase)
# Erase the chip via avrdude
add_custom_target(erase avrdude -p ${MMCU} -c ${PROG_TYPE} -e)
# Write AVR Fuses via avrdude
add_custom_target(write_fuses avrdude -p ${MMCU} -c ${PROG_TYPE} -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m)
# Read AVR Fuses via avrdude
add_custom_target(read_fuses avrdude -p ${MMCU} -c ${PROG_TYPE} -U lfuse:r:${CMAKE_SOURCE_DIR}/lfuse_readed.txt:h -U hfuse:r:${CMAKE_SOURCE_DIR}/hfuse_readed.txt:h -U efuse:r:${CMAKE_SOURCE_DIR}/efuse_readed.txt:h)
# Read AVR Fuses via avrdude
add_custom_target(read_flash avrdude -p ${MMCU} -c ${PROG_TYPE} -b 115200 -U flash:r:${CMAKE_SOURCE_DIR}/readed_firmware.hex:i)
endmacro(add_AVR_executable)



macro(AVR_link_libraries target_name)

target_link_libraries(${target_name}.elf ${ARGN})

endmacro(AVR_link_libraries)
