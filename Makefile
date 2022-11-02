CROSS_CC_PATH=~/opt/cross/bin

ECHO=echo
ASM=nasm
CC=$(CROSS_CC_PATH)/i686-elf-gcc
LD=$(CROSS_CC_PATH)/i686-elf-ld
QEMU=qemu-system-i386
GDB=gdb

CFLAGS=-g -ffreestanding -falign-jumps -falign-functions -falign-labels \
	-falign-loops -fstrength-reduce -fomit-frame-pointer \
	-finline-functions -Wno-unused-function -fno-builtin \
	-Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib \
	-nodefaultlibs -Wall -O0 -I. -std=gnu99
ASFLAGS=-f elf -g

OBJS=build/kernel.asm.o build/kernel.o build/drivers/vga/vga.o \
	build/drivers/vga/term.o build/string/string.o build/idt/idt.o \
	build/idt/idt.asm.o build/mm/mm.o build/mm/heap/heap.o \
	build/mm/heap/kheap.o build/mm/paging/paging.o \
	build/mm/paging/paging.asm.o build/io/io.asm.o

OUT=bin/navi.bin

all: build/boot/boot.asm.o build/kernel.bin
	@$(ECHO) "Linking kernel"
	@rm -rf $(OUT)
	@dd if=build/boot/boot.asm.o >> $(OUT)
	@dd if=build/kernel.bin >> $(OUT)
	@dd if=/dev/zero bs=512 count=100 >> $(OUT)

build/kernel.bin: $(OBJS)
	@$(LD) -g -relocatable $(OBJS) -o build/kernel.out
	@$(CC) -T linker.ld -o $@ $(CFLAGS) build/kernel.out

build/boot/boot.asm.o: boot/boot.asm
	@$(ECHO) "ASM\t\t"$<
	@$(ASM) -f bin $< -o $@

build/kernel.asm.o: kernel.asm
	@$(ECHO) "ASM\t\t"$<
	@$(ASM) $(ASFLAGS) $< -o $@

build/kernel.o: kernel.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) -c $< -o $@

build/drivers/vga/vga.o: drivers/vga/vga.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) -c $< -o $@

build/drivers/vga/term.o: drivers/vga/term.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) -c $< -o $@

build/string/string.o: string/string.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) -c $< -o $@

build/idt/idt.o: idt/idt.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) -c $< -o $@

build/idt/idt.asm.o: idt/idt.asm
	@$(ECHO) "ASM\t\t"$<
	@$(ASM) $(ASFLAGS) $< -o $@

build/mm/mm.o: mm/mm.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) -c $< -o $@

build/mm/heap/heap.o: mm/heap/heap.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) -c $< -o $@

build/mm/heap/kheap.o: mm/heap/kheap.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) -c $< -o $@

build/mm/paging/paging.o: mm/paging/paging.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) -c $< -o $@

build/mm/paging/paging.asm.o: mm/paging/paging.asm
	@$(ECHO) "ASM\t\t"$<
	@$(ASM) $(ASFLAGS) $< -o $@

build/io/io.asm.o: io/io.asm
	@$(ECHO) "ASM\t\t"$<
	@$(ASM) $(ASFLAGS) $< -o $@

clean:
	@rm -rf build/boot/boot.asm.o $(OBJS) $(OUT) build/kernel.out

run: all
	@$(QEMU) -hda $(OUT)

gdb: all
	@$(GDB) -x gdb_commands.txt
