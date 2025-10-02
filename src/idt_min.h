#pragma once

struct __attribute__((packed)) IdtEntry {
    uint16_t off_lo;
    uint16_t sel;
    uint8_t  zero;
    uint8_t  type_attr;   // 0x8E = present, ring0, 32-bit interrupt gate
    uint16_t off_hi;
};
struct __attribute__((packed)) Idtr {
    uint16_t limit;
    uint32_t base;
};

extern void lidt(void *idtr);
extern void isr80_stub(void);

static inline void idt_set(struct IdtEntry *idt, int n, void (*h)()){
    uint32_t p = (uint32_t)h;
    idt[n].off_lo   = p & 0xFFFF;
    idt[n].sel      = 0x08;     // kernel code selector from GRUB’s GDT
    idt[n].zero     = 0;
    idt[n].type_attr= 0x8E;     // present, DPL=0, 32-bit gate
    idt[n].off_hi   = (p >> 16) & 0xFFFF;
}

// exceptions_stub.c  (temporary)
void idt_install_exceptions(void) { /* TODO: install 0..31 and lidt */ }

