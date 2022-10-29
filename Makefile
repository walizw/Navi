ECHO=echo
CC=gcc
ASM=nasm
LD=ld

CFLAGS=-Wall -Werror -std=gnu99 -O0 -g

OBJS=build/boot/boot.asm.o
OUT=bin/navi.bin

all: $(OBJS)
	@$(ECHO) "Linking kernel"

build/boot/boot.asm.o: boot/boot.asm
	@$(ECHO) "ASM\t\t"$<
	@$(ASM) -f bin $< -o $@

clean:
	@rm -rf $(OBJS)
