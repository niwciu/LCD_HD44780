

@echo off
set PATH=C:/msys32/xtensa-lx106-elf/bin;C:/msys32/usr/bin;C:/msys32/mingw32/bin
echo =======================================================================
echo UPDATING LIBRARY FILES
echo =======================================================================
if not exist user (
    call mkdir user
) else (
    echo folder "user" exist
)
copy "..\..\..\src\lcd_hd44780.c" "user\"

if not exist include (
    call mkdir include
    echo folder "include" created
) else (
    echo folder "include" exist
)

echo Copy files to include\lcd_hd44780\
copy "..\..\..\src\lcd_hd44780.h" "include\" 
copy "..\..\..\src\lcd_hd44780_interface.h" "include\"
copy "..\..\..\src\lcd_hd44780_def_char.h" "include\"
copy "..\..\..\src\lcd_hd44780_config.h" "include\"
echo =======================================================================
echo BUILD PROJECT
echo =======================================================================

call make COMPILE=gcc BOOT=new APP=1 SPI_SPEED=40 SPI_MODE=DIO SPI_SIZE_MAP=6 all