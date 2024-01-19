#include <IO/Ports.h>
#include <Kernel/Panic.h>
#include <LibK/stdio.h>
#include <System/Exceptions.h>
#include <System/IDT.h>
#include <System/PIC.h>

__attribute__((interrupt)) void C_Int_0(struct interrupt_frame *frame) {
    kprintf("Divide By Zero Error #00\n");
}

__attribute__((interrupt)) void C_Int_1(struct interrupt_frame *frame) {
    panic("Debug Error #DB");
}
__attribute__((interrupt)) void C_Int_2(struct interrupt_frame *frame) {
    panic("NMI Interrupt #--");
}
__attribute__((interrupt)) void C_Int_3(struct interrupt_frame *frame) {
    panic("Breakpoint #BP");
}
__attribute__((interrupt)) void C_Int_4(struct interrupt_frame *frame) {
    panic("Overflow #OF");
}
__attribute__((interrupt)) void C_Int_5(struct interrupt_frame *frame) {
    panic("BOUND Range Exceeded #BR");
}
__attribute__((interrupt)) void C_Int_6(struct interrupt_frame *frame) {
    panic("Invalid Opcode #UD");
}
__attribute__((interrupt)) void C_Int_7(struct interrupt_frame *frame) {
    panic("Device Not Available #NM");
}
__attribute__((interrupt)) void C_Int_8(struct interrupt_frame *frame,
                                        uint64_t error_code) {
    panic("Double Fault #DF");
}
__attribute__((interrupt)) void C_Int_9(struct interrupt_frame *frame) {
    panic("Coprocessor Segment Overrun #NA");
}
__attribute__((interrupt)) void C_Int_10(struct interrupt_frame *frame,
                                         uint64_t error_code) {
    panic("Invalid TSS #TS");
}
__attribute__((interrupt)) void C_Int_11(struct interrupt_frame *frame,
                                         uint64_t error_code) {
    panic("Segment Not Present #NP");
}
__attribute__((interrupt)) void C_Int_12(struct interrupt_frame *frame,
                                         uint64_t error_code) {
    panic("Stack Segment Fault #SS");
}
__attribute__((interrupt)) void C_Int_13(struct interrupt_frame *frame,
                                         uint64_t error_code) {
    panic("General Protection Fault #GP");
}
__attribute__((interrupt)) void C_Int_14(struct interrupt_frame *frame,
                                         uint64_t error_code) {
    /*
    uint64_t *faultAddress;
    asm volatile("mov %%cr2, %0" : "=r"(faultAddress)::"memory");
    */
    panic("Page Fault #PF");
}
__attribute__((interrupt)) void C_Int_16(struct interrupt_frame *frame) {
    panic("FPU Floating-Point Error #MF");
}
__attribute__((interrupt)) void C_Int_17(struct interrupt_frame *frame,
                                         uint64_t error_code) {
    panic("Alignment Check #AC");
}
__attribute__((interrupt)) void C_Int_18(struct interrupt_frame *frame) {
    panic("Machine Check #MC");
}
__attribute__((interrupt)) void C_Int_19(struct interrupt_frame *frame) {
    panic("SIMD Floating-Point #XF");
}

// 20 to 31 are Intel reserved.

__attribute__((interrupt)) void
Default_INT_Handler(struct interrupt_frame *frame) {
    kprintf("Unhandled interrupt!\n");
}

void Load_Exceptions(void) {
    IDT_Add_Int(0, C_Int_0, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(1, C_Int_1, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(2, C_Int_2, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(3, C_Int_3, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(4, C_Int_4, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(5, C_Int_5, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(6, C_Int_6, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(7, C_Int_7, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(8, C_Int_8, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(9, C_Int_9, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(10, C_Int_10, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(11, C_Int_11, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(12, C_Int_12, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(13, C_Int_13, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(14, C_Int_14, IDT_FLAGS_INTERRUPT_GATE);
    // 15 is Intel reserved.
    IDT_Add_Int(15, Default_INT_Handler, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(16, C_Int_16, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(17, C_Int_17, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(18, C_Int_18, IDT_FLAGS_INTERRUPT_GATE);
    IDT_Add_Int(19, C_Int_19, IDT_FLAGS_INTERRUPT_GATE);
    for (uint8_t i = 20; i < 255; i++) {
        IDT_Add_Int(i, Default_INT_Handler, IDT_FLAGS_INTERRUPT_GATE);
    }
}
