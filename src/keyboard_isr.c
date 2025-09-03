// isr_keyboard.c
#include <stdint.h>

static inline void outb(uint16_t p, uint8_t v){ __asm__ volatile("outb %0,%1"::"a"(v),"Nd"(p)); }
static inline uint8_t inb(uint16_t p){ uint8_t v; __asm__ volatile("inb %1,%0":"=a"(v):"Nd"(p)); return v; }

typedef struct __attribute__((packed)) {
	    uint32_t eip, cs, eflags, esp, ss;
} interrupt_frame_t;

volatile unsigned kbd_hits = 0;
volatile uint8_t  kbd_last = 0;

__attribute__((interrupt))
void keyboard_isr(interrupt_frame_t *frame) {
	(void)frame;
	kbd_last = inb(0x60);   // must read to clear KBC
	kbd_hits++;
	outb(0x20, 0x20);       // EOI to master PIC
}
