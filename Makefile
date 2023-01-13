PROJ_NAME=BlobOS


BUILD_DIR ?= build
ASM ?= nasm
CC ?= cc

KERN_SRC = $(wildcard kernel/*.c)
KERN_OBJ=$(KERN_SRC:kernel/%.c=$(BUILD_DIR)/%.o)

BOOT_SRC = $(wildcard boot/*.asm)
BOOT_OBJ = $(BOOT_SRC:boot/%.asm=$(BUILD_DIR)/%.o)

FLAGS = -O2 -m32 -ffreestanding
CFLAGS += -c						\
					-W		\
					-Wall		\
					-std=gnu99	\
					$(FLAGS)
					
LDFLAGS += -T linker.ld 				\
					 -nostdlib	\
					 -z noexecstack \
					 $(FLAGS)

all: options buildFolder $(PROJ_NAME)

$(PROJ_NAME): $(KERN_OBJ) $(BOOT_OBJ)
	$(CC) $(LDFLAGS) $^ -o build/$@.bin

$(BOOT_OBJ): $(BOOT_SRC)
	nasm -felf32 $^ -o $@

build/%.o: kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

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
	@echo "ASM = $(ASM)\n"

clean:
	rm -rf build/

.PHONY: all options run run-bin buildFolder buildISO clean
