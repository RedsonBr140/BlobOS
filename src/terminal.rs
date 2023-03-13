use vga::colors::{Color16, TextModeColor};
use vga::writers::{ScreenCharacter, Text80x25, TextWriter};

pub struct Writer {
    inner: Text80x25,
    cursor_x_pos: usize,
    cursor_y_pos: usize,
}

impl Writer {
    pub fn new() -> Writer {
        let writer = Writer {
            cursor_x_pos: 0,
            cursor_y_pos: 0,
            inner: Text80x25::new(),
        };

        return writer;
    }

    pub fn write_string(&mut self, s: &str) {
        for byte in s.bytes() {
            match byte {
                0x20..=0x7e | b'\n' => self.inner.write_character(
                    self.cursor_x_pos,
                    self.cursor_y_pos,
                    ScreenCharacter::new(
                        byte,
                        TextModeColor::new(Color16::LightGrey, Color16::Black),
                    ),
                ),
                _ => self.inner.write_character(
                    self.cursor_x_pos,
                    self.cursor_y_pos,
                    ScreenCharacter::new(
                        0xfe,
                        TextModeColor::new(Color16::LightGrey, Color16::Black),
                    ),
                ),
            }
            if self.cursor_x_pos + 1 == 80 {
                self.cursor_x_pos += 1;
                self.cursor_y_pos += 1;
            }
            self.cursor_x_pos += 1;
            self.inner
                .set_cursor_position(self.cursor_x_pos, self.cursor_y_pos);
        }
    }
}

pub fn terminal_initialize(writer: &mut Writer) {
    writer.inner.set_mode();
    writer.inner.clear_screen();
}
