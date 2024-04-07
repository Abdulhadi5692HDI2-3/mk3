#include <stdint.h>
#include <stddef.h>
#include <write.h>
#include <vga/text.h>
#include <i386/cpu/gdt.h>

#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an i386-elf compiler"
#endif

#if defined(__win32__)
	#error "This code must be compiled with a cross compiler producing an ELF32 file"
#endif

void KernelOK(const char* message) {
	printf("[");
	TerminalSetColor(0x0A);
	printf("OK");
	TerminalSetColor(0x07);
	printf("] %s\n", message);
}
void kernel_main() {
	TerminalInitalize();
	KernelOK("Initalized the Terminal");
	InitGDT();
	KernelOK("Initalized the GDT!");
}