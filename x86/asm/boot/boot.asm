[org 0x7C00]      ; BIOS loads boot sector at 0x7C00

start:
    cli             ; Disable interrupts while setting up
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00  ; Temporary stack

    ; Load the kernel (assume kernel.bin is at sector 2 on the disk)
    mov ah, 0x02    ; BIOS read sector
    mov al, 1       ; number of sectors to read at a time
    mov ch, 0       ; cylinder
    mov cl, 2       ; sector (kernel starts at sector 2)
    mov dh, 0       ; head
    mov dl, 0x80    ; drive (first HDD)
    mov bx, 0x1000  ; ES:BX = 0x0000:0x1000, load kernel there
    int 0x13        ; BIOS disk read
    jc no_kernel    ; jump if error

    ; Jump to kernel entry point
    jmp 0x1000:0000

; -------------------------
no_kernel:
    mov si, msg
print_loop:
    lodsb
    cmp al, 0
    je halt_loop
    mov ah, 0x0E
    int 0x10
    jmp print_loop

halt_loop:
    cli
    hlt
    jmp halt_loop

; -------------------------
msg db "Kernel not found!", 0

; -------------------------
; Fill remaining bytes up to 510
times 510 - ($-$$) db 0
dw 0xAA55            ; Boot sector signature

