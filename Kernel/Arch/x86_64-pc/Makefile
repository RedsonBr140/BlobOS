CONFIG_ARCH ?= x86_64
CONFIG_ARCH ?= pc

override MAKEFLAGS += -rR

override KERNEL := BlobOS.elf

GIT_VERSION := $(shell git --no-pager describe --tags --always --dirty)

# Convenience macro to reliably declare user overridable variables.
define DEFAULT_VAR =
    ifeq ($(origin $1),default)
        override $(1) := $(2)
    endif
    ifeq ($(origin $1),undefined)
        override $(1) := $(2)
    endif
endef

# It is suggested to use a custom built cross toolchain to build a kernel.
# We are using the standard "cc" here, it may work by using
# the host system's toolchain, but this is not guaranteed.
override DEFAULT_CC := gcc
$(eval $(call DEFAULT_VAR,CC,$(DEFAULT_CC)))

# Same thing for "ld" (the linker).
override DEFAULT_LD := ld
$(eval $(call DEFAULT_VAR,LD,$(DEFAULT_LD)))

# User controllable C flags.
override DEFAULT_CFLAGS := -g -O2 -pipe
$(eval $(call DEFAULT_VAR,CFLAGS,$(DEFAULT_CFLAGS)))

# User controllable nasm flags.
override DEFAULT_NASMFLAGS := -F dwarf -g
$(eval $(call DEFAULT_VAR,NASMFLAGS,$(DEFAULT_NASMFLAGS)))

# User controllable linker flags. We set none by default.
override DEFAULT_LDFLAGS :=
$(eval $(call DEFAULT_VAR,LDFLAGS,$(DEFAULT_LDFLAGS)))

override CFLAGS += \
    -Wall \
    -Wextra \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-omit-frame-pointer \
    -fno-stack-check \
    -fno-lto \
    -fPIE \
    -m64 \
    -march=x86-64 \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone \
    -I Include/ \
    -I ../../Include/ \
    -DGIT_VERSION=\"$(GIT_VERSION)\"

override LDFLAGS :=	\
	-nostdlib		\
	-static			\
	-pie			\
	-z text \
	-z max-page-size=0x1000 \
	-T linker.ld

override NASMFLAGS += \
    -Wall \
    -f elf64

# Use "find" to glob all *.c, *.S, and *.asm files in the tree and obtain the
# object and header dependency file names.
CFILES := $(shell find ../../ -path ../../Arch -prune -type f -o -name '*.c')
CFILES += $(shell find ../../Arch/x86_64-pc -path . -prune -type f -o -name '*.c')
NASMFILES := $(shell find -L . -type f -name '*.asm')
OBJ := $(CFILES:.c=.c.o) $(NASMFILES:.asm=.asm.o)
HEADER_DEPS := $(CFILES:.c=.c.d) $(ASFILES:.S=.S.d)

# Default target.
.PHONY: all
all: $(KERNEL)

limine.h:
	pwd
	[ -s Include/$@ ] || curl \
	https://raw.githubusercontent.com/limine-bootloader/limine/v5.x-branch/limine.h -o Include/$@

$(KERNEL): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

# Include header dependencies.
-include $(HEADER_DEPS)

# Compilation rules for *.c files.
%.c.o: %.c limine.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation rules for *.asm (nasm) files.
%.asm.o: %.asm GNUmakefile
	nasm $(NASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)

.PHONY: distclean
distclean: clean
	rm -f limine.h
