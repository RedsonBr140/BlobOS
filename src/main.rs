#![no_std]
#![no_main]

mod terminal;

use core::panic::PanicInfo;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn _start() -> ! {
    let mut writer = terminal::Writer::new();
    terminal::terminal_initialize(&mut writer);

    writer.write_string("Hello, World!\n");

    // We want to loop because we can't return to the bootloader
    loop {}
}
