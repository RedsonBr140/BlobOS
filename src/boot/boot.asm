bits 16
org 0x7C00

%define ENDL 0x0D, 0x0A

jmp short _start 		; without this jump, the processor would attempt to execute data that isn't code.
nop

%include "src/boot/fat.asm"

_start:
	mov sp, stack_end	; Set the stack pointer.
	mov ah, 0x0		; Set video mode.
	mov al, 0x03		; 80x25, 16 colors for foreground and 8 for background.
	int 0x10		; Video interpution

	mov si, msg
	call println
	jmp $

%include "src/boot/println.asm"

msg db "Welcome to BlobOS bootloader!", ENDL, "Loading kernel...", ENDL, "Wait, there is no kernel to load!", ENDL
times 510-($-$$) db 0
dw 0xAA55

section .bss
stack_begin:
	RESB 4096
stack_end:
