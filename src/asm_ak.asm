; Josiah Welch
; 8/29/25
; Assembly code to boot Arcus kernel from Grub or other bootloader

bits 32
global lidt
lidt:
    mov eax, [esp+4]
    lidt [eax]
    ret

global isr80_stub
extern isr80_common

isr80_stub:
    push dword 0x80        ; vector number (optional but handy)
    jmp isr80_common

section .text
; Exported stubs and common handler
global irq0,irq1,irq2,irq3,irq4,irq5,irq6,irq7,irq8,irq9,irq10,irq11,irq12,irq13,irq14,irq15
global irq_common
extern irq_handler_c   ; C function we’ll write below

; Macro: push IRQ number, jump to common
%macro MAKE_IRQ 1
global irq%1
irq%1:
    push dword %1
    jmp irq_common
%endmacro

MAKE_IRQ 0
MAKE_IRQ 1
MAKE_IRQ 2
MAKE_IRQ 3
MAKE_IRQ 4
MAKE_IRQ 5
MAKE_IRQ 6
MAKE_IRQ 7
MAKE_IRQ 8
MAKE_IRQ 9
MAKE_IRQ 10
MAKE_IRQ 11
MAKE_IRQ 12
MAKE_IRQ 13
MAKE_IRQ 14
MAKE_IRQ 15

; Common shim: save regs, call C handler(vec), restore, iret
irq_common:
    ; Save general regs
    pushad
    ; Stack layout right now:
    ;  esp -> [edi,esi,ebp,esp',ebx,edx,ecx,eax] (pushad) , [irq#] (from stub)
    mov eax, [esp + 32]     ; eax = irq number pushed by stub
    push eax
    call irq_handler_c
    add esp, 4

    popad
    add esp, 4              ; drop the pushed irq number
    iretd

	align 4
	dd 0x1badb002			; Magic #
	dd 0x00					; Flags
	dd - (0x1badb002 + 0x00); Checksum 

global start
extern main_ak

start:
	call main_ak
	hlt 					; CPU halt

