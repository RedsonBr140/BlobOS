#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(blob_os::test_runner)]
#![reexport_test_harness_main = "test_main"]

mod serial;
mod terminal;

use core::panic::PanicInfo;

#[no_mangle]
pub extern "C" fn _start() -> ! {
    terminal::terminal_initialize();
    println!("Welcome to BlobOS!");

    blob_os::init();

    x86_64::instructions::interrupts::int3();

    #[cfg(test)]
    test_main();

    println!("I'm still alive!");

    // We want to loop because we can't return to the bootloader
    loop {}
}

#[cfg(not(test))]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("Kernel Panic! {}", info);
    loop {}
}

#[cfg(test)]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    blob_os::test_panic_handler(info)
}
