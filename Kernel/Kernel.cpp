#include <Arch/TextMode.hpp>
#include <Arch/multiboot.h>
#include <Kernel/Kernel.hpp>
#include <LibK/stdio.hpp>

TextMode::Terminal *termptr;

namespace Kernel {
TextMode::Terminal *GetMainTerminal() { return termptr; }
extern "C" void Panic(char *PanicMessage) {
    TextMode::Terminal panicTerminal;

    panicTerminal.SetColor(TextMode::Color::LIGHT_GREY, TextMode::Color::BLUE);
    panicTerminal.Clear();
    panicTerminal.WriteString(
        R"(
         _______
        |.-----.|
        ||x . x||
        ||_.-._||
        `--)-(--`
       __[=== o]___
      |:::::::::::|\
      `-=========-`()
)");
    panicTerminal.WriteString(PanicMessage);

    asm __volatile__("hlt");
}
}; // namespace Kernel

extern "C" void Kmain(multiboot_info_t mb_header) {
    TextMode::Terminal terminal;
    termptr = &terminal;

    terminal.SetColor(TextMode::Color::LIGHT_GREY, TextMode::Color::BLACK);
    terminal.Clear();

    terminal.WriteString("Welcome to BlobOS!\n");
}
