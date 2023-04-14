#include <Kernel.hpp>
#include <TextMode.hpp>
#include <multiboot.h>

extern "C" void Kernel::Panic(char *PanicMessage) {
    TextMode::Terminal panicTerminal;

    panicTerminal.SetColor(TextMode::Color::LIGHT_GREY, TextMode::Color::BLUE);
    panicTerminal.Clear();
    panicTerminal.WriteString(PanicMessage);

    asm __volatile__("hlt");
}

extern "C" void Kmain(multiboot_info_t mb_header) {
    TextMode::Terminal terminal;

    terminal.SetColor(TextMode::Color::LIGHT_GREY, TextMode::Color::BLACK);
    terminal.Clear();

    terminal.WriteString("Welcome to BlobOS!");
}
