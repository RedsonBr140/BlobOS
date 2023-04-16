#include <Arch/TextMode.hpp>
#include <Arch/multiboot2.h>
#include <Arch/x86_64/Interrupts/IDT.h>
#include <Kernel/Kernel.hpp>

#include <Kernel/LibK/stdio.h>

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

extern "C" void Kmain() {
    TextMode::Terminal terminal;
    termptr = &terminal;

    terminal.SetColor(TextMode::Color::LIGHT_GREY, TextMode::Color::BLACK);
    terminal.Clear();

    terminal.WriteString("Welcome to BlobOS!\n");

    idtInit();

    if (!areInterruptsEnabled()) {
        enableInterrupts();
    }
}
