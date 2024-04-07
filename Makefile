.PHONY: all
all: build

.PHONY: build
build:
	make -C kernel

.PHONY: run
run:
	qemu-system-i386 -kernel mk3.elf

.PHONY: distclean
distclean: clean

.PHONY: clean
clean:
	make -C kernel clean
	rm -rf mk3.elf