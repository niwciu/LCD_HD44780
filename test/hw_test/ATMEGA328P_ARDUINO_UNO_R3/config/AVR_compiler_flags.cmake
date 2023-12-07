set(COMPILE_OPTIONS
-mmcu=${MMCU} 
-std=gnu99 
-Os 
-Wall
-Wno-main
-Wundef
-Wstrict-prototypes
-Werror
-Wfatal-errors
-Wl,--relax,--gc-sections
-g
-gdwarf-2
-funsigned-char
-funsigned-bitfields
-fpack-struct
-fshort-enums
-ffunction-sections
-fdata-sections
-fno-split-wide-types
-fno-tree-scev-cprop
-ffreestanding #flag required by util/delay.h 
)
set(LD_FLAGS "-mmcu=${MMCU} -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS "${LD_FLAGS}")