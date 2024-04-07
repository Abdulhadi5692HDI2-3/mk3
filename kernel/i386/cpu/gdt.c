// @author Abdulhadi5692HDI2-3
// @brief Initalizes a new GDT to use
// because the grub one is now invalid
// though it is cached in the processor
// thats why it just works.
#include <i386/cpu/gdt.h>
#include <stdint.h>
#include <stddef.h>

extern void GdtLoad(uint32_t);
void SetGdtEntry(int entry, uint32_t base, uint8_t flags, uint16_t limit, uint8_t access);

typedef struct {
    uint32_t base;
    uint8_t flags;
    uint16_t limit;
    uint8_t access;
} GdtEntry;

typedef struct {
    uint16_t limit;
    uint32_t baseaddress;
} __attribute__((packed)) gdtr;

typedef struct {
    GdtEntry entries[5];
} Gdt;

Gdt GDT;
gdtr GDTr;
void InitGDT() {
    // null descriptor
    SetGdtEntry(0, 0, 0, 0, 0);
    // code segment
    SetGdtEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // data segment
    SetGdtEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // user code segment
    SetGdtEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // user data segment
    SetGdtEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    GDTr.limit = sizeof(GDT) - 1;
    GDTr.baseaddress = ((uint32_t)&GDT);
}

void SetGdtEntry(int entry, uint32_t base, uint8_t flags, uint16_t limit, uint8_t access) {
    GDT.entries[entry].base = base;
    GDT.entries[entry].limit = limit & 0xFFFF;
    GDT.entries[entry].flags = (limit >> 16) & 0xFF;
    GDT.entries[entry].flags = GDT.entries[entry].flags | (flags & 0xF0);
    GDT.entries[entry].access = access;
}