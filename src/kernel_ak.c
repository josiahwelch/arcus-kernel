// Josiah Welch
// 8/29/25
// Kernel c file

//NOTE: heavily influenced by https://github.com/chipsetx/Simple-Kernel-in-C-and-Assembly#

//#include "ps2_ak.h"
#include "define.h"
#include "keyboard.c"
#include "kern_utils_ak.h"
#include "idt.h"
#include "pic.h"

__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
	    __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}

static int vectors[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];

// Creates an IDT table
__attribute__((aligned(0x10))) 
static idt_entry_t idt[256]; // Create an array of IDT entries; aligned for performance
static idtr_t idtr;

// Helper function for entry definition
void idt_set_descriptor(unsigned char vector, void* isr, unsigned char flags);
void idt_set_descriptor(unsigned char vector, void* isr, unsigned char flags) {
	idt_entry_t* descriptor = &idt[vector];

	descriptor->isr_low        = (unsigned int)isr & 0xFFFF;
	descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
	descriptor->attributes     = flags;
	descriptor->isr_high       = (unsigned int)isr >> 16;
	descriptor->reserved       = 0;
}

void idt_init(void);
void idt_init() {
	idtr.base = (unsigned int *)&idt[0];
	idtr.limit = (unsigned short)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

	for (unsigned char vector = 0; vector < 32; vector++) {
		idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
		vectors[vector] = 1;
	}

	__asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
	__asm__ volatile ("sti"); // set the interrupt flag
}

void main_ak() {
	clear_ak();
	print_ak("Arcus kernel loaded!", 0);
	print_ak("Arcus OS is loading...", 1);

	idt_init();

	enable_cursor(4, 5);
	char *msg = (char *)0xFFEE00;
	int i = 0;
	msg = "        \0";
	while (1) {
		if (i > 7) {i = 0;}
		msg[i] = get_ascii_char();
		//unsigned short *x_ptr = (unsigned short *)CURSOR_POS_X;
		print_ak(msg, 2);
		update_cursor(i, 3);
		//if (msg[i] == 'A') {move_cursor_up();}
		i++;
	}

	if (get_key() == KEY_1_PRESSED) {
		print_ak("1 key pressed!", 2);
	}
}
