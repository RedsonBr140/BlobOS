project('BlobOS', ['cpp', 'nasm'], version: '0.1.1')

source_root = meson.source_root()
grub_mkrescue = find_program('grub-mkrescue', 'grub2-mkrescue')

# g++ -T Arch/x86_64/linker.ld -o BlobOS.bin -ffreestanding -O2 -nostdlib boot.o Kernel.o TextMode.o -m32
# g++ -O2 -m32 -ffreestanding -c -W -Wall -Wextra -std=c++17 -mno-sse Kernel/Kernel.cpp Arch/x86_64/TextMode.cpp -IArch/Include

global_flags = ['-O0', '-ffreestanding', '-m32']
cpp_flags = ['-c', '-W', '-Wall', '-Wextra', '-std=c++17', '-mno-sse', '-g', global_flags]
link_args = ['-T', f'@source_root@/Arch/x86_64/linker.ld', '-nostdlib', '-z', 'noexecstack', global_flags]
nasm_flags = ['-f', 'elf32']

# kernel_inc, kernel_sources
subdir('Kernel')
# arch_inc, arch_sources, x86_64_inc
subdir('Arch')

binary = executable('BlobOS.bin',
  sources: [ arch_sources, kernel_sources ],
  link_args: link_args,
  cpp_args : cpp_flags,
  nasm_args: nasm_flags,
  include_directories: [ arch_inc, kernel_inc, x86_64_inc ]
)
