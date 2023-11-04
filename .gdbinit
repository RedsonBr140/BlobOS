set architecture i386:x86-64
# AT&T syntax is awful
set disassembly-flavor intel

# Pretty-printing :)
enable pretty-printer

# Cool layout
layout split

file Kernel/Arch/x86_64-pc/BlobOS.elf

target remote :1234
