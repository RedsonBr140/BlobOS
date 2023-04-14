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

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top ; Set the esp register to the top of the stack, as it grows downwards.

	; note, that if you are building on Windows, C functions may have "_" prefix in assembly: _kernel_main
	extern Kmain
	; EBX holds the pointer to the Multiboot info structure.
	push ebx
	call Kmain
	add esp, 8
.hang: 
	hlt
	jmp .hang
.end:
