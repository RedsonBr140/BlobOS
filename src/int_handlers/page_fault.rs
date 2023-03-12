use x86_64::structures::idt::{InterruptStackFrame, PageFaultErrorCode};

pub extern "x86-interrupt" fn page_fault_handler(
    _stack_frame: InterruptStackFrame,
    error_code: PageFaultErrorCode,
) {
    use x86_64::registers::control::Cr2;

    panic!(
        r#"EXCEPTION: PAGE FAULT
Accessed Address: {:?}
Error code: {:?}"#,
        Cr2::read(),
        error_code
    );
}
