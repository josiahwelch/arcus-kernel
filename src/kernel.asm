[org 0x7E00]
[bits 16]

; Print kernel message
mov si, kernel_msg
call print_string

; Halt system
cli
hlt

; Print string routine
print_string:
    mov ah, 0x0E
.loop:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .loop
.done:
    ret

; Kernel message
kernel_msg db 'Arca Kernel is initialized!', 0
