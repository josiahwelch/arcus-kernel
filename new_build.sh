#!/bin/sh
set -e

CC=${CC:-cc}
NASM=${NASM:-nasm}

BUILD=build
SRC=../src

mkdir -p "$BUILD"
rm -f "$BUILD"/*
cd "$BUILD"

# 1) Assemble 32-bit, non-PIC
$NASM -f elf32 -F dwarf -g "$SRC/asm_ak.asm" -o asm_ak.o

# 2) Compile C as 32-bit, freestanding, NO PIE/PIC
CFLAGS="-m32 -ffreestanding -fno-pie -fno-pic -fno-stack-protector -fno-builtin -O2 -Wall -Wextra"
$CC $CFLAGS -c "$SRC/kernel_ak.c" -o kernel_ak.o

# 3) Link via the compiler driver, NO PIE, with your linker script
LDFLAGS="-m32 -nostdlib -no-pie -Wl,-T,$SRC/linker.ld -Wl,--build-id=none"
# On OpenBSD, -no-pie might be spelled -nopie; try both:
$CC $LDFLAGS -o kernel asm_ak.o kernel_ak.o || \
  $CC "${LDFLAGS/-no-pie/-nopie}" -o kernel.elf asm_ak.o kernel_ak.o

  cd ..
