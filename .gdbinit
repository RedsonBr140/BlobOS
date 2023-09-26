set architecture i386:x86-64
# AT&T syntax is awful
set disassembly-flavor intel
file Kernel/Arch/x86_64-pc/BlobOS.elf

target remote :1234
