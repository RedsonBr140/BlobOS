use vga::colors::{Color16, TextModeColor};
use vga::writers::{ScreenCharacter, Text80x25, TextWriter};

pub struct Writer {
    inner: Text80x25,
    cursor_x_pos: usize,
    cursor_y_pos: usize,
    color: TextModeColor,
}

impl Writer {
    pub fn new() -> Writer {
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

    pub fn write_string(&mut self, s: &str) {
        for byte in s.bytes() {
            match byte {
                b'\n' => self.new_line(),
                _ => {
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
}

pub fn terminal_initialize(writer: &mut Writer) {
    writer.inner.set_mode();
    writer.inner.clear_screen();
}
