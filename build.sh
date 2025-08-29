#!/bin/sh
mkdir build
cd build/
nasm -f elf32 ../src/asm_ak.asm -o asm_ak.o
egcc -m32 -c ../src/kernel_ak.c -o kernel_ak.o
ld -m elf_i386 -T ../src/linker.ld -o kernel asm_ak.o kernel_ak.o
cd ..
