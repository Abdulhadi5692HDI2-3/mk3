#include <i386/cpu/idt.h>
#include <i386/cpu/pic.h>
#include <i386/cpu/pit.h>
#include <other.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <write.h>

// functions
extern void* IsrStubTable[];
void IdtSetDescriptor(uint8_t Vector, void* ISR, uint8_t Flags);

// i have no idea what this is for (check the idt tutorial that most if this is based off)
static bool vectors[256];

// IDT Entry struct
typedef struct {
    uint16_t IsrLow;
    uint16_t CodeSegment;
    uint8_t NotUsed;
    uint8_t Flags;
    uint16_t IsrHigh;
} __attribute__((packed)) IdtEntry;


// IDTR struct
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) Idtr;


// IDT (aligned)
// We have 256 entries
__attribute__((aligned(0x10)))
static IdtEntry IDT[256];

// Idtr
static Idtr IDTR;

// Exception Handler
// shouldnt return
void ExceptionHandler();
void ExceptionHandler() {
    KernelERROR("CPU Exception!");
    __asm__ volatile ("cli; hlt");
}

// Initalize IDT
void InitIDT() {
    IDTR.base = (uintptr_t)&IDT;
    IDTR.limit = (uint16_t)sizeof(IdtEntry) * 256 - 1;
    
    // remap the pic
    RemapPIC(0x20, 0x28);
    for (uint8_t vector = 0; vector < 32; vector++) {
        IdtSetDescriptor(vector, IsrStubTable[vector], 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(IDTR)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag

}

void IdtSetDescriptor(uint8_t Vector, void* ISR, uint8_t Flags) {
    IdtEntry* Descriptor = &IDT[Vector];

    Descriptor->IsrLow = (uint32_t)ISR & 0xFFFF;
    Descriptor->CodeSegment = 0x08;
    Descriptor->Flags = Flags;
    Descriptor->IsrHigh = (uint32_t)ISR >> 16;
    Descriptor->NotUsed = 0;
}
