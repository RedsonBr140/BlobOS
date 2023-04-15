%ifndef BOOT_GDT_ASM
%define BOOT_GDT_ASM

; Access bits
%define GDT_PRESENT        1 << 7
%define GDT_NOT_SYS        1 << 4
%define GDT_EXEC           1 << 3
%define GDT_DC             1 << 2
%define GDT_RW             1 << 1
%define GDT_ACCESSED       1 << 0

; Flags bits
%define GDT_GRAN_4K        1 << 7
%define GDT_SZ_32          1 << 6
%define GDT_LONG_MODE      1 << 5

section .gdt
align 8

gdt_null:
    dq 0
gdt_code:
	dd 0xFFFF           ; Limit & Base (low, bits 0-15)
    db 0                ; base (mid, bits 16-23)
    db GDT_PRESENT | GDT_NOT_SYS | GDT_EXEC | GDT_RW ; access
    db GDT_GRAN_4K | GDT_LONG_MODE | 0xF      ; flags & limit (high, bits 16-19)
    db 0                ; base (high, bits 24-31)
gdt_data:
    dd 0xFFFF           ; limit & base (low, bits 0-15)
    db 0                ; base (mid, bits 16-23)
    db GDT_PRESENT | GDT_NOT_SYS | GDT_RW          ; access
    db GDT_GRAN_4K | GDT_SZ_32 | 0xF         ; flags & limit (high, bits 16-19)
    db 0                ; base (high, bits 24-31)
gdt_tss:
	dd 0x00000068
	dd 0x00CF8900
gdt_end:
gdt_descriptor:
	dw gdt_end - gdt_null - 1
	dq gdt_null
%endif

; gdt_descriptor:
; dw gdt_end - gdt_null - 1
; dq gdt_null
; dq gdt_code
; dq gdt_data
; dq gdt_tss
