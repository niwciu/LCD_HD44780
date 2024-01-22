# Compiler flags used for C and ASM files
set(CORE_FLAGS "${MCPU} -mthumb")

# Debug flag
if(CMAKE_BUILD_TYPE=="Debug")
    set(CORE_FLAGS "${CORE_FLAGS} -g3")
endif()

# Hardware float support
set(CORE_FLAGS "${CORE_FLAGS} -mfloat-abi=soft")

#enable showing compile diagnostic output colored (ninja require this opctions to show colored errors)
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	set(CORE_FLAGS "${CORE_FLAGS} -fdiagnostics-color=always")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
	set(CORE_FLAGS "${CORE_FLAGS} -fcolor-diagnostics")
endif()

# Use newlib-nano, links with libc_nano.a
# set(CORE_FLAGS "${CORE_FLAGS} --specs=nano.specs")

# Compiler flags specific for C++ files
# -std - C++ standard: c++98, gnu++98, c++11, gnu++11, c++14, gnu++14
# -fno-rtti - disable virtual class information used by dynamic_cast and typeid
# -fno-exceptions - disable exception handling
# fverbose-asm - additional comments for generated assembler code
# -MMD - create dependency files
set(CXX_FLAGS "-std=gnu++14 -Os -g3 -fno-rtti -fno-exceptions -fverbose-asm -MMD")

# Compiler flags specific for C files
# -std - C standard: c89, c99, gnu89,gnu99, iso9899:119409
# -Os - optimization level: -O0, -O1, -O2, -O3, -Os
# fverbose-asm - additional comments for generated assembler code
# -MMD - create dependency files
#  -fstack-usage - enable stack usage analysis
#  -fcyclomatic-complexity ->TBC
set(C_FLAGS "-std=gnu11 -Os -ffunction-sections -fdata-sections -fverbose-asm -MMD -fstack-usage --specs=nano.specs ")

set(ASM_FLAGS "-c -x assembler-with-cpp --specs=nano.specs")

# Warning flags for C++
# -Wall - standard warnings
# -Wextra - extended warnings
set(CXX_WARNINGS "-Wall -Wextra")

# Warning flags for C
# -Wall - standard warnings
# -Wextra - extended warnings
# -Wstrict-prototypes - additional warnings for function prototypes
set(C_WARNINGS "-Wall -Wextra -Wstrict-prototypes")

set(LD_SCRIPT ${CMAKE_SOURCE_DIR}/linker.ld)
# Linker flags
# -Wl, -Map - map file to be created
# -T - file with linker script
#  --specs=nosys.specs -> links with libnosys.a
# -g - debug flag
# -Wl,--gc-sections - unused function removal
# -Wl,--print-memory-usage -> as the flag says :)
# -Wl,--start-group -lc -lm 
# -Wl,--end-group
set(LD_FLAGS "-Wl,-Map=\"${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.map\",--cref -T\"${LD_SCRIPT}\" --specs=nosys.specs -Wl,--gc-sections -Wl,--print-memory-usage")

set(CMAKE_CXX_FLAGS "${CORE_FLAGS} ${CXX_FLAGS} ${CXX_WARNINGS}")
set(CMAKE_C_FLAGS "${CORE_FLAGS} ${C_FLAGS} ${C_WARNINGS}")
set(CMAKE_ASM_FLAGS "${ASM_FLAGS} ${CORE_FLAGS} ${CXX_WARNINGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CORE_FLAGS} ${LD_FLAGS}")