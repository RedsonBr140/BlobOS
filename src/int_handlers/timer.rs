use crate::cpu::interrupts::{InterruptIndex, PICS};
use x86_64::structures::idt::InterruptStackFrame;

pub extern "x86-interrupt" fn timer_input_handler(_stack_frame: InterruptStackFrame) {
    unsafe {
        PICS.lock()
            .notify_end_of_interrupt(InterruptIndex::Timer.as_u8());
    }
}
