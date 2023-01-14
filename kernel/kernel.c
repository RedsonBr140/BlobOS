#include "include/terminal.h"

void kernel_main(void) {
  /* Initialize terminal interface */
  terminal_initialize();
  terminal_writestring("Hello, BlobOS's kernel here.\n");
}
