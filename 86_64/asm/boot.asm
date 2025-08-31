[org 0x7C00]
bits 16

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:protected_mode

; -------------------------------
; 32-bit Protected Mode
; -------------------------------
[bits 32]
protected_mode:
    mov eax, cr4
    or eax, 1 << 5     
    mov cr4, eax

    mov eax, pml4_table
    mov cr3, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8      
    wrmsr

    mov eax, cr0
    or eax, 0x80000000 
    mov cr0, eax

    jmp 0x10:long_mode

; -------------------------------
; 64-bit Long Mode
; -------------------------------
[bits 64]
long_mode:
    mov rsi, msg
    call print_string
    jmp kernel_main    

print_string:
    mov rax, 0xB8000
.next:
    lodsb
    test al, al
    jz .done
    mov [rax], al
    inc rax
    mov byte [rax], 0x07
    inc rax
    jmp .next
.done:
    ret

msg db "Booting 64-bit kernel...", 0

; GDT setup
gdt_start:
    dq 0x0000000000000000
    dq 0x00AF9A000000FFFF 
    dq 0x00AF92000000FFFF 

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

gdt_end:

; Dummy page table (identity map)
align 4096
pml4_table:
    dq pdpt_table | 0x03
align 4096
pdpt_table:
    dq pd_table | 0x03
align 4096
pd_table:
    dq 0x00000000 | 0x83

times 510 - ($ - $$) db 0
dw 0xAA55
