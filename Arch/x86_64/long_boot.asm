[bits 64]
global Realm64

extern Kmain

Realm64:
	cli
	mov ax, 0x10
	mov ds, ax                    ; Set the data segment to the A-register.
    mov es, ax                    ; Set the extra segment to the A-register.
    mov fs, ax                    ; Set the F-segment to the A-register.
    mov gs, ax                    ; Set the G-segment to the A-register.
    mov ss, ax                    ; Set the stack segment to the A-register.

	call Kmain
.hang:
	hlt
	jmp .hang
