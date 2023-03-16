#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(blob_os::test_runner)]
#![reexport_test_harness_main = "test_main"]

use blob_os::init;
use core::panic::PanicInfo;

#[no_mangle] // don't mangle the name of this function
pub extern "C" fn _start() -> ! {
    init();
    test_main();

    loop {}
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    blob_os::test_panic_handler(info)
}

#[test_case]
fn breakpoint_exception() {
    x86_64::instructions::interrupts::int3();
}
