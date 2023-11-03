CONFIG_ARCH ?= x86_64
CONFIG_TARGET ?= pc

NAME ?= BlobOS
ISO_IMAGE := $(NAME).iso
KERNEL_ELF := $(NAME).elf

.PHONY: all
all: $(ISO_IMAGE)

.PHONY: limine
limine:
	make -C limine

.PHONY: kernel
kernel:
	make -C Kernel/Arch/$(CONFIG_ARCH)-$(CONFIG_TARGET)

$(ISO_IMAGE): limine kernel
	rm -rf build
	mkdir -p build/iso_root/boot/
	cp Kernel/Arch/$(CONFIG_ARCH)-$(CONFIG_TARGET)/$(KERNEL_ELF) \
		limine.cfg limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin \
		build/iso_root/boot/
	ls build/
	xorriso -as mkisofs -b boot/limine-bios-cd.bin -no-emul-boot \
		-boot-load-size 4 -boot-info-table --efi-boot boot/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		build/iso_root/ -o build/${ISO_IMAGE}
		limine/limine bios-install build/${ISO_IMAGE}

.PHONY: clean
clean:
	rm -rf build *.iso *.img *.tar *.tar.gz
	$(MAKE) -C Kernel/Arch/$(CONFIG_ARCH)-$(CONFIG_TARGET) clean

.PHONY: distclean
distclean: clean
	$(MAKE) -C Kernel/Arch/$(CONFIG_ARCH)-$(CONFIG_TARGET) distclean