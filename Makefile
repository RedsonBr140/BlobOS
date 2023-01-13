PROJ_NAME=BlobOS

ASSEMBLER =nasm
KERN_SRC = $(wildcard ./kernel/*.c wildcard ./kernel/*.h)
BOOT_SRC = $(wildcard ./boot/*.asm)
BOOT_OBJ = $(subst .asm,.o,$(subst boot/,build/,$(BOOT_SRC)))
KERN_OBJ = $(subst .c,.o,$(subst kernel/,build/,$(KERN_SRC)))
BUILD_DIR ?= build
CFLAGS += -c							\
					-W							\
					-Wall						\
					-O2							\
					-m32						\
					-std=gnu99			\
					-ffreestanding	\

LDFLAGS += -T linker.ld 	\
					 -O2						\
					 -m32						\
					 -nostdlib			\
					 -ffreestanding \
					 -z noexecstack

all: options buildFolder $(PROJ_NAME)

$(PROJ_NAME): $(KERN_OBJ) $(BOOT_OBJ)
	$(CC) $? -o $(BUILD_DIR)/$@.bin $(LDFLAGS)

$(BOOT_OBJ): $(BOOT_SRC)
	$(ASSEMBLER) -felf32 $< -o $@

$(KERN_OBJ): $(KERN_SRC)
	$(CC) $< -o $@ $(CFLAGS)

buildISO: $(PROJ_NAME)
	cp $(BUILD_DIR)/$<.bin $(BUILD_DIR)/isodir/boot/
	cp boot/grub.cfg $(BUILD_DIR)/isodir/boot/grub/
	grub-mkrescue -o $(BUILD_DIR)/$<.iso $(BUILD_DIR)/isodir

run: all buildISO
	@echo "Running!"
	qemu-system-i386 -cdrom build/$(PROJ_NAME).iso -audiodev pa,id=audio0 -machine pcspk-audiodev=audio0

run-bin: all 
	@echo "Running!"
	qemu-system-i386 -kernel build/$(PROJ_NAME).bin -audiodev pa,id=audio0 -machine pcspk-audiodev=audio0



buildFolder:
	@mkdir -p $(BUILD_DIR)/isodir/boot/grub

options: 
	@echo $(PROJ_NAME) build options:
	@echo "CFLAGS = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo "CC = $(CC)"
	@echo "ASSEMBLER = $(ASSEMBLER)\n"

