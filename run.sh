#!/usr/bin/bash
# requires: ovmf in /usr/share/ovmf
cp /usr/share/ovmf/OVMF.fd ./bios.bin
qemu-system-x86_64 -pflash bios.bin -cdrom mk3.iso
