[org 0x7C00]

start:
    cli                     ; Disable interrupts while setting up
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00          ; Temporary stack

    ; -------------------------
    ; Load kernel (multiple sectors)
    ; -------------------------
    mov bx, 0x1000          ; ES:BX = load address
    mov cx, 2               ; starting sector (sector 2)
    mov si, 8               ; number of sectors to load (adjust to kernel size)
    mov dl, 0x80            ; first HDD

load_sector:
    mov ah, 0x02            ; BIOS read sector
    mov al, 1                ; read 1 sector at a time
    mov ch, 0
    mov cl, cx               ; current sector
    mov dh, 0
    int 0x13
    jc no_kernel             ; jump if error

    add bx, 512              ; move pointer to next sector in memory
    inc cx                    ; next sector
    dec si
    jnz load_sector

    ; -------------------------
    ; Jump to kernel entry point
    ; -------------------------
    jmp 0x1000:0000

; -------------------------
; Error: kernel not found
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

; Fill remaining bytes up to 510
times 510-($-$$) db 0
dw 0xAA55                ; Boot signature
