ASSEMBLER=nasm
SRC_DIR=src
BUILD_DIR=build

.PHONY: all floppy_image kernel bootloader run

floppy_image: $(BUILD_DIR)/main_floppy.img

$(BUILD_DIR)/main_floppy.img: bootloader #kernel There's no kernel
	dd if=/dev/zero of=$(BUILD_DIR)/main_floppy.img bs=512 count=2880
	mkfs.fat -F 12 $(BUILD_DIR)/main_floppy.img
	dd if=$(BUILD_DIR)/bootloader.bin of=$(BUILD_DIR)/main_floppy.img conv=notrunc
	mcopy -i $(BUILD_DIR)/main_floppy.img $(BUILD_DIR)/kernel.bin "::kernel.bin"

kernel: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: builddir
	$(ASSEMBLER) $(wildcard $(SRC_DIR)/kernel/*) -f bin -o $(BUILD_DIR)/kernel.bin

bootloader: $(BUILD_DIR)/bootloader.bin

$(BUILD_DIR)/bootloader.bin: builddir
	$(ASSEMBLER) $(SRC_DIR)/boot/boot.asm -f bin -o $(BUILD_DIR)/bootloader.bin

builddir:
	@mkdir -p $(BUILD_DIR)

run: floppy_image
	@echo "Running"
	@qemu-system-i386 -drive file=$(BUILD_DIR)/main_floppy.img,format=raw -audiodev pa,id=audio0 -machine pcspk-audiodev=audio0
