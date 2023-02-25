project('BlobOS', ['c', 'nasm'], version: '0.1.0')

source_root = meson.source_root()
grub_mkrescue = find_program('grub-mkrescue')

global_flags = ['-O2', '-m32', '-ffreestanding']
c_flags = ['-c', '-W', '-Wall', '-std=gnu99', global_flags]
link_args = ['-T', f'@source_root@/linker.ld', '-nostdlib', '-z', 'noexecstack', global_flags]
nasm_flags = ['-f', 'elf32']

subdir('kernel')
subdir('boot')

binary = executable('BlobOS.bin',
  sources: [boot_sources, kernel_sources],
  link_args: link_args,
  c_args : c_flags,
  nasm_args: nasm_flags,
  include_directories: 'kernel/include'
)

iso = custom_target(
    'BlobOS.iso',
    input : binary,
    output : 'BlobOS.iso',
    command : [
      'mkdir', '-p', 'isodir/boot/grub', '&&',
      'cp', '@INPUT@', 'isodir/boot/', '&&',
      'cp', f'@source_root@/boot/grub.cfg', 'isodir/boot/grub', '&&',
      grub_mkrescue, '-o', '@OUTPUT@', 'isodir'
    ],
    build_by_default : true,
    install : false,
)

run_target(
  'run.bin',
  command : ['tools/build-and-run.sh', 'bin'],
)

run_target(
  'run.iso',
  command : ['tools/build-and-run.sh', 'iso'],
)
