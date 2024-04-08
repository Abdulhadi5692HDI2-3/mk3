#include <i386/cpu/pit.h>
#include <basicio.h>
#include <write.h>

uint32_t tick = 0;

void pit_callback() {
    tick++;
    printf("Tick: %d\n", tick);
}

void InitalizePIT(uint32_t Frequency) {
    uint32_t divisor = 1193180 / Frequency;
    outb(0x43, 0x36);

    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    outb(0x40, low);
    outb(0x40, high);
}