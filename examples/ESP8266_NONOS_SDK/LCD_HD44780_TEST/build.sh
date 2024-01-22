#!/bin/bash -x
echo "make_lib.sh version 20160307"

# $env:PATH = "C:/msys32/xtensa-lx106-elf/bin;C:/msys32/usr/bin;C:/msys32/mingw32/bin";
export PATH="C:/msys32/xtensa-lx106-elf/bin;C:/msys32/usr/bin;C:/msys32/mingw32/bin"
make clean
make COMPILE=gcc BOOT=new APP=1 SPI_SPEED=40 SPI_MODE=DIO SPI_SIZE_MAP=6 all