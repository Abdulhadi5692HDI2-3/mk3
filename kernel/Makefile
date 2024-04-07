# kernel makefile
override KERNEL_OUT := mk3.elf

override CC := i386-elf-gcc
override CFLAGS += \
	-std=gnu99 \
	-ffreestanding \
	-O2 \
	-Wall \
	-Wextra \

override CFILES := $(shell find -L * -type f -name '*.c')
override ASFILES := $(shell find -L * -type f -name '*.s')
override NASMFILES := $(shell find -L * -type f -name '*.asm')
override OBJ := $(CFILES:.c=.c.o) $(ASFILES=:.s=.s.o) $(NASMFILES=:.asm=.asm.o)

.PHONY: all
all: $(KERNEL_OUT)

$(KERNEL_OUT): $(OBJ)
	$(CC) $(CFLAGS) -c boot.S -o boot.S.o
	nasm i386/cpu/setgdt.asm -f elf32 -o i386/cpu/setgdt.asm.o
	$(CC) -T ../linker.ld -o ../$@ -ffreestanding -O2 -nostdlib boot.S.o i386/cpu/setgdt.asm.o $^ -lgcc

%.c.o: %.c
	$(CC) $(CFLAGS) -I . -c $^ -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ)
	rm -rf boot.S.o