#![feature(abi_x86_interrupt)]
#![no_std]
#![no_main]

use blob_os::{exit_qemu, serial_print, serial_println, QemuExitCode};
use core::panic::PanicInfo;
use lazy_static::lazy_static;
use x86_64::structures::idt::{InterruptDescriptorTable, InterruptStackFrame};

lazy_static! {
    static ref TEST_IDT: InterruptDescriptorTable = {
        let mut idt = InterruptDescriptorTable::new();
        unsafe {
            idt.double_fault
                .set_handler_fn(test_double_fault_handler)
                .set_stack_index(blob_os::cpu::gdt::DOUBLE_FAULT_IST_INDEX);
        }

        idt
    };
}

#[no_mangle]
pub extern "C" fn _start() -> ! {
    serial_print!("\x1b[36mshould_panic::should_fail\x1b[0m...\t");
    blob_os::cpu::gdt::init();
    init_test_idt();

    stack_overflow();

    panic!("Continued after stack overflow (how?)");
}

fn stack_overflow() {
    stack_overflow();
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    blob_os::test_panic_handler(info)
}

pub fn init_test_idt() {
    TEST_IDT.load();
}

extern "x86-interrupt" fn test_double_fault_handler(
    _stack_frame: InterruptStackFrame,
    _error_code: u64,
) -> ! {
    serial_println!("[ok]");
    exit_qemu(QemuExitCode::Success);
    loop {}
}
