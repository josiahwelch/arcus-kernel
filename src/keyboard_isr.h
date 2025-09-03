// isr_keyboard.c
#include <stdint.h>

// --- port I/O ---
static inline void outb(uint16_t p, uint8_t v){ __asm__ volatile("outb %0,%1"::"a"(v),"Nd"(p)); }
static inline uint8_t inb(uint16_t p){ uint8_t v; __asm__ volatile("inb %1,%0":"=a"(v):"Nd"(p)); return v; }

// Frame layout expected by GCC for i386 interrupt handlers without error code
struct interrupt_frame {
	uint32_t ip;
	uint32_t cs;
	uint32_t flags;
	uint32_t sp;
	uint32_t ss;
};

volatile unsigned kbd_hits = 0;
volatile uint8_t  kbd_scancode = 0;

// IMPORTANT: keep this tiny; no prints, no floats, no SSE.
__attribute__((interrupt))
void keyboard_isr(struct interrupt_frame* frame) {
	(void)frame;
	kbd_scancode = inb(0x60); // drains controller buffer
	kbd_hits++;
	outb(0x20, 0x20);         // EOI (master PIC)
}
