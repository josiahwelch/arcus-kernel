; Josiah Welch
; 8/29/25
; Assembly code to boot Arcus kernel from Grub or other bootloader

; NOTE: heavily influenced by https://github.com/chipsetx/Simple-Kernel-in-C-and-Assembly#

bits 32
default rel ; Make all symbol references PC-relative

; Macros for IDT
%macro isr_err_stub 1
isr_stub_%+%1:
	call exception_handler
	iret 
%endmacro
%macro isr_no_err_stub 1
	isr_stub_%+%1:
	call exception_handler
	iret
%endmacro

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
section .data ; Move table to .data section
global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    32 
    dd isr_stub_%+i - $$ ; Store relative offset from section start
	%assign i i+1 
	%endrep

section .text
	align 4
	dd 0x1badb002			; Magic #
	dd 0x00					; Flags
	dd - (0x1badb002 + 0x00); Checksum 

global start
extern main_ak
global switch_task

switch_task:
    ; Save current task's state
	mov eax, [esp + 4] ; Pointer to current task's Task struct
	mov [eax], esp     ; Save ESP
	mov [eax + 4], ebx ; Save EIP (approximate, adjust as needed)

	; Load next task's state
	mov eax, [esp + 8] ; Pointer to next task's Task struct
	mov esp, [eax]     ; Restore ESP
	mov ebx, [eax + 4] ; Restore EIP
	jmp ebx            ; Jump to next task

start:
	cli						; Stops interrupts
	call main_ak
	hlt 					; CPU halt
