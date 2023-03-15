use core::fmt::{Arguments, Result, Write};
use core::result::Result::Ok;
use lazy_static::lazy_static;
use spin::Mutex;
use vga::colors::{Color16, TextModeColor};
use vga::writers::{ScreenCharacter, Text80x25, TextWriter};

pub struct Writer {
    inner: Text80x25,
    cursor_x_pos: usize,
    cursor_y_pos: usize,
    color: TextModeColor,
}

const WIDTH: usize = 80;
const HEIGHT: usize = 25;

lazy_static! {
    pub static ref WRITER: Mutex<Writer> = Mutex::new(Writer::new());
}

impl Writer {
    fn new() -> Writer {
        let writer = Writer {
            cursor_x_pos: 0,
            cursor_y_pos: 0,
            inner: Text80x25::new(),
            color: TextModeColor::new(Color16::LightGrey, Color16::Black),
        };

        return writer;
    }

    pub fn new_screen_character(&self, byte: u8) -> ScreenCharacter {
        ScreenCharacter::new(byte, self.color)
    }

    fn new_line(&mut self) {
        self.cursor_y_pos += 1;
        self.cursor_x_pos = 0;
    }

    fn scroll_up(&mut self) {
        for y in 0..HEIGHT - 1 {
            for x in 0..WIDTH {
                let character = self.inner.read_character(x, y + 1);
                self.inner.write_character(x, y, character);
            }
        }
        let blank = self.new_screen_character(b' ');
        for x in 0..WIDTH {
            self.inner.write_character(x, HEIGHT, blank);
        }

        self.cursor_y_pos -= 1;
    }

    pub fn write_string(&mut self, s: &str) {
        for byte in s.bytes() {
            match byte {
                b'\n' => self.new_line(),
                _ => {
                    if self.cursor_y_pos >= HEIGHT {
                        self.scroll_up();
                    }

                    self.inner.write_character(
                        self.cursor_x_pos,
                        self.cursor_y_pos,
                        self.new_screen_character(byte),
                    );
                    self.cursor_x_pos += 1;
                }
            }
            self.inner
                .set_cursor_position(self.cursor_x_pos, self.cursor_y_pos);
        }
    }

    pub fn clear_screen(&mut self, color: TextModeColor) {
        self.color = color;
        self.inner.clear_screen();
        self.color = color;
    }
    pub fn reset_cursor(&mut self) {
        self.cursor_x_pos = 0;
        self.cursor_y_pos = 0;
        self.inner
            .set_cursor_position(self.cursor_x_pos, self.cursor_y_pos);
    }
}

impl Write for Writer {
    fn write_str(&mut self, s: &str) -> Result {
        self.write_string(s);
        Ok(())
    }
}

pub fn terminal_initialize() {
    WRITER.lock().inner.set_mode();
    WRITER.lock().inner.clear_screen();
}

#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => ($crate::terminal::_print(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! println {
    () => {
        $crate::print!("\n")
    };
    ($($arg:tt)*) => ($crate::print!("{}\n", format_args!($($arg)*)));
}

#[doc(hidden)]
pub fn _print(args: Arguments) {
    WRITER.lock().write_fmt(args).unwrap();
}

#[test_case]
fn test_println() {
    println!("Hey, it does print to the screen!");
}

#[test_case]
fn test_println_massive() {
    for i in 0..75 {
        println!("Printed {i} times");
    }
}
