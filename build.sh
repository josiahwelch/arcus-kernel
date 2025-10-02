#!/bin/sh
mkdir build
pushd build/
nasm -f elf32 ../src/asm_ak.asm -o asm_ak.o
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-omit-frame-pointer -c ../src/kernel_ak.c -o kernel_ak.o
#ld -m elf_i386 -T ../src/linker.ld -o kernel asm_ak.o kernel_ak.o
gcc -m32 -ffreestanding -nostdlib \
    -Wl,-T,../src/linker.ld -Wl,-z,max-page-size=0x1000 -Wl,-z,noexecstack \
    -o kernel \
    kernel_ak.o asm_ak.o\
    -lgcc
popd
