set architecture i386:x86-64
# AT&T syntax is awful
set disassembly-flavor intel
file build/BlobOS.bin

target remote :1234
