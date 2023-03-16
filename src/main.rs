#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(blob_os::test_runner)]
#![reexport_test_harness_main = "test_main"]

mod serial;
mod terminal;

use core::panic::PanicInfo;

use blob_os::hlt_loop;

#[no_mangle]
pub extern "C" fn _start() -> ! {
    terminal::terminal_initialize();
    blob_os::init();

    println!("Welcome to BlobOS!");

    #[cfg(test)]
    test_main();

    hlt_loop();
}

#[cfg(test)]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    blob_os::test_panic_handler(info)
}

#[cfg(not(test))]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    use vga::colors::{Color16, TextModeColor};
    terminal::WRITER
        .lock()
        .clear_screen(TextModeColor::new(Color16::LightGrey, Color16::Blue));
    for _ in 0..(80 * 25) {
        print!("{}", ' ');
    }
    terminal::WRITER.lock().reset_cursor();

    println!(
        r#"
         _______
        |.-----.|
        ||x . x||
        ||_.-._||
        `--)-(--`
       __[=== o]___
      |:::::::::::|\
      `-=========-`()
    "#
    );

    println!("Kernel Panic! {}", info);
    hlt_loop();
}
