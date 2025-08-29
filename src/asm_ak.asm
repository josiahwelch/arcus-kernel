; Josiah Welch
; 8/29/25
; Assembly code to boot Arca kernel from Grub

; NOTE: heavily influenced by https://github.com/chipsetx/Simple-Kernel-in-C-and-Assembly#

section .text
	align 4
	dd 0x1badb002			; Magic #
	dd 0x00					; Flags
	dd - (0x1badb002 + 0x00); Checksum

global start
extern main_ak

start:
	cli						; Stops interrupts
	call main_ak
	hlt 					; CPU halt
