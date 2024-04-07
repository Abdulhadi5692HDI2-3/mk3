#include <vga/text.h>
#include <libk/string.h>
#include <libk/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// helper functions
static inline uint8_t EntryVgaColor(enum VgaColorPalette fg, enum VgaColorPalette bg) {
	return fg | bg << 4;
}
 
static inline uint16_t FindVgaEntry(unsigned char usigchar, uint8_t color)  {
	return (uint16_t) usigchar | (uint16_t) color << 8;
}

const size_t VgaWidth = 80;
const size_t VgaHeight = 25;

size_t CurrentRow;
size_t CurrentColumn;

uint8_t TerminalColor;
uint16_t* TerminalBuffer;

void TerminalInitalize() {
    CurrentRow = 0;
    CurrentColumn = 0;
    TerminalColor = EntryVgaColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    TerminalBuffer = (uint16_t*)0xb8000;
    for (size_t row = 0; row < VgaHeight; row++) {
        for (size_t col = 0; col < VgaWidth; col++) {
            const size_t Entry = row * VgaWidth + col;
			TerminalBuffer[Entry] = FindVgaEntry(' ', TerminalColor);
        }
    }
}

void TerminalSetColor(uint8_t color) {
    TerminalColor = color;
}

void TerminalPutCharAt(char letter, uint8_t color, size_t xpos, size_t ypos) {
    const size_t Entry = ypos * VgaWidth + xpos;
    TerminalBuffer[Entry] = FindVgaEntry(letter, color);
}

void TerminalPutChar(char letter) {
    if (letter == '\n') {
        CurrentColumn = 0;
        CurrentRow++;
        return;
    }
    TerminalPutCharAt(letter, TerminalColor, CurrentColumn, CurrentRow);
    if (++CurrentColumn == VgaWidth) {
        CurrentColumn = 0;
        if (++CurrentRow == VgaHeight) {
            CurrentRow = 0;
        }
    }
}

// we dont need now any other functions since we can just use a printf
// we already implemented a putchar