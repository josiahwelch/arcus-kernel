typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
	__asm__ volatile ("cli; hlt"); // Completely hangs the computer
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
	    idt_entry_t* descriptor = &idt[vector];

		    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
			    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
				    descriptor->attributes     = flags;
					    descriptor->isr_high       = (uint32_t)isr >> 16;
						    descriptor->reserved       = 0;
}

// Creates an IDT table
__attribute__((aligned(0x10))) 
static idt_entry_t idt[256]; // Create an array of IDT entries; aligned for performance

// Defines an IDTR
static idtr_t idtr;



