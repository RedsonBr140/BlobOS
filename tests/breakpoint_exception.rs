#![no_std]
#![no_main]

use blob_os::{exit_qemu, init, serial_print, serial_println, QemuExitCode};
use core::panic::PanicInfo;
use x86_64;

#[no_mangle]
pub extern "C" fn _start() -> ! {
    init();
    should_fail();
    serial_println!("[test did not panic]");
    exit_qemu(QemuExitCode::Failed);

    loop {}
}

fn should_fail() {
    serial_print!("\x1b[36mbreakpoint_exception::should_fail\x1b[0m...\t");
    x86_64::instructions::interrupts::int3();
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    serial_println!("\x1b[1;32m[ok]\x1b[0m");
    exit_qemu(QemuExitCode::Success);
    loop {}
}
