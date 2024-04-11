#!/usr/bin/env bash
# install-expects: mtools xorriso
dd if=/dev/zero of=BootNoEmul.img bs=1k count=2880
mformat -i BootNoEmul.img ::
mmd -i BootNoEmul.img ::/EFI
mmd -i BootNoEmul.img ::/EFI/BOOT
mcopy -i BootNoEmul.img bootloader/BOOTX64.EFI ::/EFI/BOOT

# make iso
mkdir iso
cp BootNoEmul.img iso
xorriso -as mkisofs -R -f -e BootNoEmul.img -no-emul-boot -o mk3.iso iso
