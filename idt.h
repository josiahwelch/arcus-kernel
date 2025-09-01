#define IDT_H
#ifndef IDH_H
typedef struct {
	unsigned short isr_low;      // The lower 16 bits of the ISR's address
	unsigned short kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	unsigned char reserved;     // Set to zero
	unsigned char attributes;   // Type and attributes; see the IDT page
	unsigned short isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
		uint16_t	limit;
			uint32_t	base;
} __attribute__((packed)) idtr_t;
#endif
