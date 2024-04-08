#include <other.h>
#include <write.h>
#include <vga/text.h>
void _putchar(char character) {
	TerminalPutChar(character);
}

void KernelOK(const char* message) {
	printf("[");
	TerminalSetColor(0x0A);
	printf("OK");
	TerminalSetColor(0x07);
	printf("] %s\n", message);
}

void KernelERROR(const char* message) {
	printf("[");
	TerminalSetColor(0x04);
	printf("ERROR");
	TerminalSetColor(0x07);
	printf("] %s\n", message);
}