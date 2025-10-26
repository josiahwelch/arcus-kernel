#include <stdint.h>
typedef void (*irq_fn_t)(void);
static irq_fn_t irqs[16];

void irq_register(uint8_t n, irq_fn_t fn){ irqs[n] = fn; }

/*
// called from your NASM irq_common with irq 0..15 
void irq_handler_c(uint32_t irq){
    extern void outb(uint16_t, uint8_t);
    if (irq < 16 && irqs[irq]) irqs[irq]();   // fan out
    if (irq >= 8) outb(0xA0, 0x20);           // EOI
    outb(0x20, 0x20);
}
*/
