#include <Arch/TextMode.hpp>
#include <Arch/multiboot2.h>
#include <Arch/x86_64/Interrupts/IDT.h>
#include <Kernel/Kernel.hpp>
#include <Kernel/LibK/stdlib.h>

#include <Kernel/LibK/stdio.h>

TextMode::Terminal *termptr;

namespace Kernel {
TextMode::Terminal *GetMainTerminal() { return termptr; }
extern "C" void Panic(const char *PanicMessage, const char *file,
                      const int line) {
    TextMode::Terminal panicTerminal;
    char *buf = (char *)"";

    itoa(line, buf, 10);

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
    panicTerminal.WriteString("Kernel Panic! Error: ");
    panicTerminal.WriteString(PanicMessage);
    panicTerminal.WriteString("\n\nPanicked at: ");
    panicTerminal.WriteString(file);
    panicTerminal.WriteString(":");
    panicTerminal.WriteString(buf);

    asm __volatile__("hlt");
}
}; // namespace Kernel

extern "C" void Kmain() {
    TextMode::Terminal terminal;
    termptr = &terminal;

    terminal.SetColor(TextMode::Color::LIGHT_GREY, TextMode::Color::BLACK);
    terminal.Clear();

    idtInit();
    if (!areInterruptsEnabled()) {
        enableInterrupts();
    }

    terminal.WriteString("Welcome to BlobOS!\n");
}
