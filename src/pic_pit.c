/* Remap 8259 PIC: master->0x20..0x27, slave->0x28..0x2F */
void pic_remap(void){
    uint8_t a1 = inb(0x21), a2 = inb(0xA1);

    outb(0x20, 0x11);  // ICW1: init, expect ICW4
    outb(0xA0, 0x11);

    outb(0x21, 0x20);  // ICW2: master vector offset 0x20
    outb(0xA1, 0x28);  // ICW2: slave  vector offset 0x28

    outb(0x21, 0x04);  // ICW3: tell Master about Slave at IRQ2
    outb(0xA1, 0x02);  // ICW3: tell Slave its cascade identity

    outb(0x21, 0x01);  // ICW4: 8086 mode
    outb(0xA1, 0x01);

    outb(0x21, a1);    // restore masks
    outb(0xA1, a2);
}

/* Mask/unmask a single IRQ line (0..15) */
void pic_unmask(uint8_t irq){
    uint16_t port = (irq < 8) ? 0x21 : 0xA1;
    uint8_t bit   = (irq < 8) ? irq   : (irq - 8);
    uint8_t val   = inb(port);
    val &= ~(1u << bit);
    outb(port, val);
}

/* Send End Of Interrupt */
static inline void pic_eoi(uint8_t irq){
    if (irq >= 8) outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

/* PIT channel 0 @ hz */
void pit_init(uint32_t hz){
    uint32_t div = 1193182u / hz;
    outb(0x43, 0x36);           // ch0, lo/hi, mode 3
    outb(0x40, (uint8_t)(div & 0xFF));
    outb(0x40, (uint8_t)(div >> 8));
}

/* Minimal VGA print (no scroll) for visible feedback */
static volatile uint16_t* const VGA = (uint16_t*)0xB8000;
static uint16_t vpos;
static void vprint(const char* s){
    while(*s){ VGA[vpos++] = (uint8_t)(*s++) | (uint16_t)(0x07 << 8); }
}

/*
volatile uint32_t g_ticks;  // 100 Hz wraps after ~497 days — fine for now

void irq_handler_c(uint32_t irq){
    if (irq == 0){                    // timer
        g_ticks++;
        if ((g_ticks % 100) == 0)     // ~1s at 100 Hz
            vprint("tick\n");
    }
    // (optional) consume keyboard scancodes to avoid buffer fill:
    if (irq == 1){ (void)inb(0x60); }

    pic_eoi(irq);
}
*/
