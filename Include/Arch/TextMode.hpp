#pragma once
#include <stddef.h>

// TODO: Write an <cstdint> implementation.
#include <stdint.h>

namespace TextMode {
static constexpr size_t VGA_WIDTH = 80;
static constexpr size_t VGA_HEIGHT = 25;

enum class Color : uint8_t {
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_BROWN,
    WHITE,
};

class Terminal {
  public:
    Terminal()
        : terminalRow(0), terminalColumn(0), terminalColor(),
          terminalBuffer((uint16_t *)0xB8000){};
    void Clear();
    void SetColor(enum Color fg, enum Color bg);
    void Write(const char *data, size_t size);
    void WriteString(const char *data);

  private:
    size_t terminalRow;
    size_t terminalColumn;

    uint8_t terminalColor;
    uint16_t *terminalBuffer;

    void updateCursor(int x, int y);
    static uint8_t vgaEntryColor(enum Color fg, enum Color bg);
    static uint16_t vgaEntry(unsigned char uc, uint8_t color);
    void putEntryAt(char c, uint8_t color, size_t x, size_t y);
    void scroll(void);
    void putChar(char c);
};
} // namespace TextMode
