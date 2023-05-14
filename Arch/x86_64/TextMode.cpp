#include <Kernel/LibK/string.h>
#include <Arch/TextMode.hpp>
#include <Kernel/IOPorts.hpp>
#include <stddef.h>
#include <stdint.h>

namespace TextMode {

/*
 * Public functions:
 */

void Terminal::Clear() {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = x + VGA_WIDTH * y;
            this->terminalBuffer[index] =
                this->vgaEntry(' ', this->terminalColor);
        }
    }
    updateCursor(this->terminalRow, this->terminalColumn);
}

void Terminal::SetColor(enum Color fg, enum Color bg) {
    this->terminalColor = vgaEntryColor(fg, bg);
}

/*
 * Private functions:
 */

void Terminal::updateCursor(int x, int y) {
    uint16_t position = y * VGA_WIDTH + x;

    Port VGAIndex(0x3D4);
    Port VGAData(0x3D5);

    VGAIndex.Write(0x0F);
    VGAData.Write((uint8_t)(position & 0xFF));
    VGAIndex.Write(0x0E);
    VGAData.Write((uint8_t)((position >> 8) & 0xFF));
}

uint8_t Terminal::vgaEntryColor(enum Color fg, enum Color bg) {
    return static_cast<uint8_t>(fg) | static_cast<uint8_t>(bg) << 4;
}

uint16_t Terminal::vgaEntry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}

void Terminal::putEntryAt(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;

    if (index >= VGA_WIDTH * VGA_HEIGHT) {
        // TODO: std::cout
        // k_printf("Error: Attempted to write to an invalid memory address "
        //          "(row=%d, col=%d)\n",
        //          this->terminalRow, this->terminalColumn);
        return;
    }

    this->terminalBuffer[index] = vgaEntry(c, color);
}

void Terminal::scroll(void) {
    // Scroll the buffer up by one row.
    const size_t buffer_size = (VGA_HEIGHT - 1) * VGA_WIDTH;

    memmove(this->terminalBuffer, this->terminalBuffer + VGA_WIDTH,
            buffer_size * 2);

    // Clear the last row.
    const size_t last_row_offset = VGA_HEIGHT - 1;
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        this->putEntryAt(' ', this->terminalColor, x, last_row_offset);
    }
}

void Terminal::PutChar(char c) {
    if (c == '\n') {
        if (this->terminalRow + 1 == VGA_HEIGHT) {
            this->scroll();
            // If we have reached the last line, we won't be able to go to
            // another line, so we reset the column to the first position.
            this->terminalColumn = 0;
        } else {
            // Move the cursor to the beginning of the next line.
            this->terminalRow++;
            this->terminalColumn = 0;
        }
    } else {
        // Put the character at the current cursor position and update
        // the cursor position to the next position.
        this->putEntryAt(c, this->terminalColor, this->terminalColumn,
                         this->terminalRow);
        this->updateCursor(this->terminalColumn + 1, this->terminalRow);

        // If the cursor reaches the end of the line, move it to the
        // beginning of the next line. If we have reached the last line,
        // scroll the terminal.
        if (++this->terminalColumn == VGA_WIDTH) {
            this->terminalColumn = 0;
            if (++this->terminalRow == VGA_HEIGHT) {
                this->scroll();
            }
        }
    }
}

void Terminal::Write(const char *data, size_t size) {
    for (size_t i = 0; i < size; i++)
        this->PutChar(data[i]);
}

void Terminal::WriteString(const char *data) {
    this->Write(data, strlen(data));
}

} // namespace TextMode
