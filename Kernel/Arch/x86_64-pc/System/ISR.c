#include <Kernel/Panic.h>
#include <System/ISR.h>

void isr_handler(Registers *frame);
void isr_handler(Registers *frame) { panic("ISR Fuckin' fucked!"); }