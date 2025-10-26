struct __attribute__((packed)) IdtEntry {
    uint16_t off_lo, sel;
    uint8_t  zero, type_attr; // For type_attr, 0x8E = present, ring0. 32-bit interrupt gate
    uint16_t off_hi;
};

extern void lidt(void*);  // if you already have a NASM/GAS lidt; else inline below
static inline void lidt_inline(void* idtr){ __asm__ __volatile__("lidt (%0)"::"r"(idtr)); }

extern void irq0(void),irq1(void),irq2(void),irq3(void),irq4(void),irq5(void),irq6(void),irq7(void),
            irq8(void),irq9(void),irq10(void),irq11(void),irq12(void),irq13(void),irq14(void),irq15(void);

static struct IdtEntry idt[256];
static struct Idtr idtr;

/* Call this after you’ve already installed the 0..31 exception handlers */
void idt_install_irqs(void){
    void (*vec[16])(void) = {
        irq0,irq1,irq2,irq3,irq4,irq5,irq6,irq7,
        irq8,irq9,irq10,irq11,irq12,irq13,irq14,irq15
    };
	for (int i = 0; i < 16; i++)
        idt_set(idt, 32 + i, vec[i]);   // vectors 0x20..0x2F

    idtr.limit = sizeof(idt) - 1;
    idtr.base  = (uint32_t)idt;

    /* Use your existing lidt; if not, the inline version works */
    #ifdef HAVE_LIDT_FUNC
      lidt(&idtr);
    #else
      lidt_inline(&idtr);
    #endif
}

