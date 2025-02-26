#!/bin/bash

export PATH="$PATH:$HOME/esp/xtensa-lx106-elf/bin"

echo "======================================================================="
echo "UPDATING LIBRARY FILES"
echo "======================================================================="

# Sprawdzenie i tworzenie folderu "user"
if [ ! -d "user" ]; then
    mkdir user
    echo "Folder 'user' created"
else
    echo "Folder 'user' exists"
fi

# Kopiowanie pliku lcd_hd44780.c do folderu user
cp "../../../src/lcd_hd44780.c" "user/"

# Sprawdzenie i tworzenie folderu "include"
if [ ! -d "include" ]; then
    mkdir include
    echo "Folder 'include' created"
else
    echo "Folder 'include' exists"
fi

# Kopiowanie plików do folderu include
echo "Copy files to include/lcd_hd44780/"
cp "../../../src/lcd_hd44780.h" "include/"
cp "../../../src/lcd_hd44780_GPIO_interface.h" "include/"
cp "../../../src/lcd_hd44780_def_char.h" "include/"
cp "../../../src/lcd_hd44780_config.h" "include/"
cp "../../../src/lcd_hd44780_driver_commands.h" "include/"

echo "======================================================================="
echo "BUILD PROJECT"
echo "======================================================================="

# Wywołanie polecenia make
make COMPILE=gcc BOOT=new APP=1 SPI_SPEED=40 SPI_MODE=DIO SPI_SIZE_MAP=6 all