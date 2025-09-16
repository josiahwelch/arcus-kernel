; Josiah Welch
; 8/29/25
; Assembly code to boot Arcus kernel from Grub or other bootloader

bits 32
section .text
	align 4
	dd 0x1badb002			; Magic #
	dd 0x00					; Flags
	dd - (0x1badb002 + 0x00); Checksum 

global start
extern main_ak

start:
	call main_ak
	hlt 					; CPU halt
