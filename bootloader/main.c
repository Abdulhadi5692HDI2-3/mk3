#include <uefi.h>

char* kernelPath = "\\kernel.elf";

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	if (argc > 0) {
		kernelPath = argv[1];
		printf("custom kernel path passed on cmdline. %s selected instead of \\\\kernel.elf", kernelPath);
	}
	FILE* kernel;

	printf("Hello world!\n");
	return 0;
}
