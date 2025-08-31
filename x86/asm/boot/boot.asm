[org 0x7C00]          ; BIOS loads bootloader here

start:
    mov ax, 0x1000    ; Load kernel to 0x1000:0000
    mov es, ax
    mov bx, 0x0000

    mov ah, 0x02      ; BIOS: read sectors
    mov al, 1         ; Read 1 sector
    mov ch, 0         ; Cylinder
    mov cl, 2         ; Sector (start at 2)
    mov dh, 0         ; Head
    mov dl, 0x80      ; First hard disk
    int 0x13
    jc no_kernel      ; If carry flag set, read failed

    jmp 0x1000:0000   ; Jump to kernel

no_kernel:
    mov si, msg
    call print_string

    mov cx, 10
countdown:
    mov ah, 0x0E
    mov al, '0'
    add al, cl
    int 0x10
    mov al, '.'
    int 0x10
    mov al, '.'
    int 0x10
    mov al, '.'
    int 0x10

    call delay
    loop countdown

    cli
    hlt

print_string:
    mov ah, 0x0E
.next_char:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .next_char
.done:
    ret

delay:
    mov cx, 0xFFFF
.wait:
    loop .wait
    ret

msg db "OS not found. Shutting down in ", 0

times 510 - ($ - $$) db 0
dw 0xAA55
