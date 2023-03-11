; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0			; align loaded modules on page boundaries
MEMINFO  equ  1 << 1			; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC	 equ  0x1BADB002		; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS)   ; checksum of above, to prove we are multiboot

; Declare a multiboot header that marks the program as a kernel. These are magic
; values that are documented in the multiboot standard. The bootloader will
; search for this signature in the first 8 KiB of the kernel file, aligned at a
; 32-bit boundary. The signature is in its own section so the header can be
; forced to be within the first 8 KiB of the kernel file.
section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

; The multiboot standard does not define the value of the stack pointer register
; (esp) and it is up to the kernel to provide a stack. This allocates room for a
; small stack by creating a symbol at the bottom of it, then allocating 16384
; bytes for it, and finally creating a symbol at the top. The stack grows
; downwards on x86. The stack is in its own section so it can be marked nobits,
; which means the kernel file is smaller because it does not contain an
; uninitialized stack. The stack on x86 must be 16-byte aligned according to the
; System V ABI standard and de-facto extensions. The compiler will assume the
; stack is properly aligned and failure to align the stack will result in
; undefined behavior.
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

section .data
loading db "Loading GDT...", 0xA, 0
loaded db "Loaded GDT!", 0

%include "boot/gdt.asm"

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top ; Set the esp register to the top of the stack, as it grows downwards.

	extern terminal_initialize
	extern k_printf
	extern k_printok
	; We are initializing the terminal in the assembly code. 
	; If the kernel fails, at least the screen will be cleared. :trollface:
	call terminal_initialize

	push loading
	call k_printf
	add esp, 4

	lgdt [gdt_descriptor] ; Loading the GDT table
	mov ax, 0x10 ; We want to reload the code segment
	; Reloading the segment registers
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	push loaded
	call k_printok
	add esp, 4

	; As we're inside an "old" function in the code segment, we have to jump to the new one.
	; Specifying the value inside CS, in this case, 0x08.
	jmp 0x08:.code
.code:
	; note, that if you are building on Windows, C functions may have "_" prefix in assembly: _kernel_main
	extern kernel_main
	; EBX holds the pointer to the Multiboot info structure.
	push ebx
	call kernel_main
	add esp, 8
.hang: 
	hlt
	jmp .hang
.end:
