#include <stdint.h>
#include <stddef.h>
#include <write.h>
#include <vga/text.h>
#include <i386/cpu/gdt.h>
#include <i386/cpu/idt.h>
#include <i386/cpu/pit.h>
#include <other.h>
#include <basicio.h>

#define uchar unsigned char

void kernel_main() {
	TerminalInitalize();
	KernelOK("Initalized the Terminal");
	InitGDT();
	KernelOK("Initalized the GDT!");
	InitIDT();
	KernelOK("Initalized the IDT and interrupts should be working.");
}