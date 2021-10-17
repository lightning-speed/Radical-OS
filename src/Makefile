OBJDIR = ../lib
BUILDDIR = ../bin

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CSRC = $(call rwildcard,./,*.c)
ASMSRC = $(call rwildcard,./,*.asm)
OBJS += $(patsubst %.c, $(OBJDIR)/%.o, $(CSRC))
OBJS += $(patsubst %.asm, $(OBJDIR)/%_asm.o, $(ASMSRC))

#OBJS = $(OBJDIR)/Drivers/gdt.o $(OBJDIR)/Drivers/idt.o $(OBJDIR)/Drivers/Keyboard.o $(OBJDIR)/Drivers/Screen.o $(OBJDIR)/FS/vfs.o

CC = gcc
ASM = nasm
LD = ld


CFLAGS = -std=gnu99 -m32 -I. -fno-stack-protector
ASMFLAGS = -f elf32
LDFLAGS = -m elf_i386

kernel.elf: $(OBJS)
	@echo LD $^
	@$(LD) $(LDFLAGS) -o $(BUILDDIR)/$@.tmp $^

	objcopy -Felf32-i386 $(BUILDDIR)/$@.tmp $(BUILDDIR)/$@

	@echo "\n\nCompiled using asm: $(ASM), cc: $(CC), ld: $(LD)\n\n"

$(OBJDIR)/%.o: %.c
	@echo "CC $^ -> $@"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $^

$(OBJDIR)/%_asm.o: %.asm
	@echo "ASM $^ -> $@"
	@mkdir -p $(@D)
	@$(ASM) $(ASMFLAGS) -o $@ $^

run: kernel.elf
	qemu-system-i386 -kernel $(BUILDDIR)/kernel.elf -machine type=pc-i440fx-3.1

