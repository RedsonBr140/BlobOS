#![no_std]
#![no_main]

mod terminal;

use core::panic::PanicInfo;

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("Kernel Panic! {}", info);
    loop {}
}

#[no_mangle]
pub extern "C" fn _start() -> ! {
    terminal::terminal_initialize();

    println!("Welcome to BlobOS!");
    // We want to loop because we can't return to the bootloader
    loop {}
}
