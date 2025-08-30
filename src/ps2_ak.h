#ifndef PS2_AK_H
#define PS2_AK_H

// Define standard integer types for freestanding environment
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

// I/O port access
void outb(uint16_t port, uint8_t value) {
	asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

uint8_t inb(uint16_t port) {
	uint8_t value;
	asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

// Scan code to ASCII table (set 1, basic keys)
const char scancode_to_ascii[] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
	0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
	// Add more if you want
};

// Dummy print function (replace with your kernel’s)
void print_char(char c) {
	// Replace this with your kernel’s console output
	// For now, just pretend it prints
}

// Process scan code
void process_scancode(uint8_t scancode) {
	if (scancode & 0x80) {
		// Key release, ignore for simplicity
		return;
	}
	char c = scancode_to_ascii[scancode & 0x7F];
	if (c) {
		print_ak(c, 2);
	}
}

// Keyboard interrupt handler
void keyboard_handler() {
	uint8_t scancode = inb(0x60);
	process_scancode(scancode);
	// Send End of Interrupt to PIC
	outb(0x20, 0x20);
}

// Set up IDT entry (dummy, replace with your kernel’s)
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
	// Replace with your IDT setup code
	// Example: IRQ 1 (keyboard) at interrupt 33 (0x20 + 1)
}

// Initialize PS/2 controller
void ps2_init() {
	// Disable keyboard to clear junk
	outb(0x64, 0xAD);
	while (inb(0x64) & 0x1) // Clear buffer
	inb(0x60);
							    
	// Enable keyboard
	outb(0x64, 0xAE);
										    
	// Enable scanning
	outb(0x60, 0xF4);
	while (inb(0x64) & 0x2); // Wait for input buffer empty
	// Wait for ACK (0xFA)
	while (inb(0x64) & 0x1) {
		if (inb(0x60) == 0xFA) break;
	}
}

// Initialize keyboard
void keyboard_init() {
	ps2_init();
	// Hook IRQ 1 to keyboard handler
	idt_set_gate(33, (uint32_t)keyboard_handler, 0x08, 0x8E);
	// Enable interrupts
	asm volatile ("sti");
}
#endif
