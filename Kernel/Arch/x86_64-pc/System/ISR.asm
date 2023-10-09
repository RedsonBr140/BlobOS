[bits 64]
[extern isr_handler]

%macro PUSHAQ 0
    push rax
    push rcx
    push rdx
    push rbx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro POPAQ 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rbx
    pop rdx
    pop rcx
    pop rax
%endmacro


%macro ISR_NO_ERR 1
global ISR_STUB_%1
ISR_STUB_%1:
    push 0      ; Dummy error code
    push %1     ; interrupt number
    jmp isr_common
%endmacro

%macro ISR_ERR 1
global ISR_STUB_%1
ISR_STUB_%1:
    ; These error codes are pushed by the processor itself
    push %1     ; interrupt number
    jmp isr_common
%endmacro

isr_common:
    PUSHAQ
    cld
    push rsp
    call isr_handler
    POPAQ
    

ISR_NO_ERR 0
ISR_NO_ERR 1
ISR_NO_ERR 2
ISR_NO_ERR 3
ISR_NO_ERR 4
ISR_NO_ERR 5
ISR_NO_ERR 6
ISR_NO_ERR 7
ISR_ERR 8
ISR_NO_ERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NO_ERR 15
ISR_NO_ERR 16
ISR_ERR 17
ISR_NO_ERR 18
ISR_NO_ERR 19
ISR_NO_ERR 20
ISR_ERR 21
ISR_NO_ERR 22
ISR_NO_ERR 23
ISR_NO_ERR 24
ISR_NO_ERR 25
ISR_NO_ERR 26
ISR_NO_ERR 27
ISR_NO_ERR 28
ISR_NO_ERR 29
ISR_NO_ERR 30
ISR_NO_ERR 31

%assign i 32
%rep 224 ; 255 - 32 whats what we've gone through already
    ISR_NO_ERR i
    %assign i i+1
%endrep

global isr_stub_table
isr_stub_table:
%assign i 0
%rep 256
    dq ISR_STUB_%+i
%assign i i+1
%endrep