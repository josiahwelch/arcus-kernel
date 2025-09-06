; Josiah Welch
; 8/29/25
; Assembly code to boot Arcus kernel from Grub or other bootloader

bits 32

section .bss
align 16
stack_area:        resb 16384      ; 16 KiB
stack_top:

%macro isr_err_stub 1
isr_stub_%+%1:
    call exception_handler
	iret 
%endmacro

; if writing for 64-bit, use iretq instead
%macro isr_no_err_stub 1
isr_stub_%+%1:
	call exception_handler
	iret
%endmacro

; Using these two macros...
extern exception_handler
isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

; Stub table
global isr_stub_table
isr_stub_table:
	%assign i 0 
	%rep    32 
		dd isr_stub_%+i ; use DQ instead if targeting 64-bit
	%assign i i+1 
	%endrep

section .text
	align 4
	dd 0x1badb002			; Magic #
	dd 0x00					; Flags
	dd - (0x1badb002 + 0x00); Checksum 

global start
extern main_ak

start:
	cli						; Stops interrupts
	mov     esp, stack_top
	xor     ebp, ebp
	call main_ak
	hlt 					; CPU halt
