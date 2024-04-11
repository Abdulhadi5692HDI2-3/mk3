# Makefile
# build bootloader
all: buildb buildk

buildb:
	make -C bootloader

buildk:
	# unsupported

clean:
	make -C bootloader clean_
	rm -rf mk3.iso
	rm -rf iso
	rm -rf bios.bin
	rm -rf BootNoEmul.img

buildiso:
	./buildiso.sh

run:
	./run.sh
