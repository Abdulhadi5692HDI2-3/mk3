#include <i386/cpu/pic.h>
#include <basicio.h>

// The Programmable Interrupt Controller
#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA PIC1+1
#define PIC2_COMMAND PIC2
#define PIC2_DATA PIC2+1

#define PIC_ENDOFINTERRUPT 0x20

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

void SendEOI(uint8_t Irq) {
    if (Irq >= 8) {
        outb(PIC2_COMMAND, PIC_ENDOFINTERRUPT);
    }
    outb(PIC1_COMMAND, PIC_ENDOFINTERRUPT);
}


void RemapPIC(int offset1, int offset2) {
    uint8_t a1, a2;

    // save masks
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC1_DATA, offset1);
    io_wait();
    outb(PIC2_DATA, offset2);
    io_wait();
    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    // restore saved masks
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}

void DisablePIC(void) {
    outb(PIC1_DATA, 0xff);
    outb(PIC2_DATA, 0xff);
}