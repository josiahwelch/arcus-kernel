[org 0x7C00]
[bits 16]

; Print boot message
mov si, boot_msg
call print_string

; Load kernel from disk (sector 2)
mov ax, 0x7E00        ; Kernel load address
mov es, ax
xor bx, bx            ; Buffer offset
mov ah, 0x02          ; BIOS read sector
mov al, 1             ; Number of sectors
mov ch, 0             ; Cylinder
mov dh, 0             ; Head
mov cl, 2             ; Sector (1=boot, 2=kernel)
int 0x13              ; BIOS disk interrupt

; Jump to kernel
jmp 0x7E00

; Print string routine
print_string:
    mov ah, 0x0E      ; BIOS teletype
.loop:
    lodsb             ; Load next char
    cmp al, 0         ; Check for null terminator
    je .done
    int 0x10          ; Print char
    jmp .loop
.done:
    ret

; Bootloader message
boot_msg db 'Arca bootloader initialized!', 0

; Fill to 512 bytes and add boot signature
times 510-($-$$) db 0
dw 0xAA55
