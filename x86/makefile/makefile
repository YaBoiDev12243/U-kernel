CC = i686-elf-gcc
LD = i686-elf-ld
ASM = nasm
QEMU = qemu-system-i386

CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -m elf_i386 -T linker.ld

SRC = kernel.c UVgaHandler.c
OBJ = $(SRC:.c=.o)

all: os-image.bin

boot.bin: boot.asm
	$(ASM) -f bin $< -o $@

kernel.bin: $(OBJ) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

os-image.bin: boot.bin kernel.bin
	cat boot.bin kernel.bin > $@
	dd if=/dev/zero bs=512 count=2880 >> $@ 2>/dev/null

run: os-image.bin
	$(QEMU) -fda os-image.bin

clean:
	rm -f *.o *.bin os-image.bin
