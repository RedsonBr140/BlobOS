[bits 64]
[global reloadSegments]

reloadSegments:
    push 0x08 ; Push code segment to stack
    lea rax, [rel .reload_CS] ; Load address of .reload_CS into RAX
    push rax ; Push this value to the stack
    retfq ; Perform a far return
    .reload_CS:
    ; Reload data segment registers
    mov ax, 0x10 ; 0x10 is the 64-bit data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
