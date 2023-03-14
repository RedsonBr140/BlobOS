#![no_std]
#![no_main]

use blob_os::{exit_qemu, serial_print, serial_println, QemuExitCode};
use core::panic::PanicInfo;

#[no_mangle]
pub extern "C" fn _start() -> ! {
    should_fail();
    serial_println!("[test did not panic]");
    exit_qemu(QemuExitCode::Failed);

    loop {}
}


fn should_fail() {
    serial_print!("\x1b[36mshould_panic::should_fail\x1b[0m...\t");
    assert_eq!(0, 1);
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    serial_println!("\x1b[1;32m[ok]\x1b[0m");
    exit_qemu(QemuExitCode::Success);
    loop {}
}
