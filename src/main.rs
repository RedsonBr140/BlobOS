#![no_std]
#![no_main]

mod vga_buffer;

use core::panic::PanicInfo;

use vga::colors::{Color16, TextModeColor};
use vga::writers::{ScreenCharacter, Text80x25, TextWriter};

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn _start() -> ! {
    let text_mode = Text80x25::new();
    let color = TextModeColor::new(Color16::LightGrey, Color16::Black);
    let screen_char = ScreenCharacter::new(b'H', color);

    text_mode.set_mode();
    text_mode.clear_screen();
    text_mode.write_character(0, 0, screen_char);
    loop {}
}
