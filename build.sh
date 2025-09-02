#!/bin/sh
mkdir build
cd build/
nasm -f elf32 ../src/asm_ak.asm -o asm_ak.o
egcc -m32 -c ../src/kernel_ak.c -o kernel_ak.o
#egcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -mno-red-zone -c ../src/kernel_ak.c -o kernel_ak.o
egcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie \
    -fno-asynchronous-unwind-tables -fno-exceptions -fno-rtti -fPIC \
	-c ../src/kernel_ak.c -o kernel_ak.o
ld -m elf_i386 -T ../src/linker.ld -nostdlib -o kernel asm_ak.o kernel_ak.o
cd ..
