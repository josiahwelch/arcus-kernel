// Josiah Welch
// 8/29/25
// Kernel c file

#include "define.h"
#include <stdint.h>
#include <stdbool.h>
#include "io_ak.h"
#include "keyboard.c"
#include "kern_utils_ak.h"
#include "idt_min.h"

__attribute__((naked)) void isr80_common(void){
    __asm__ __volatile__ (
        "pushal\n\t"               /* save eax..edi (32 bytes) */
        /* esp now points to saved EDI; the vector we pushed in the stub is 32 bytes below */
        "mov 32(%esp), %eax\n\t"   /* eax = vector number (0x80) if you need it */

        /* demo side-effect: write 'A' (0x41) with attribute 0x07 at VGA[0] */
        "mov $0xB8000, %eax\n\t"
        "mov $0x0741,  %dx\n\t"
        "mov %dx, (%eax)\n\t"

        "popal\n\t"                /* restore regs */
        "add $4, %esp\n\t"         /* drop pushed vector from the stub */
        "iret\n\t"                 /* return from interrupt */
    );
}

char test_input[16];

void main_ak(void){
	clear_ak();
	print_ak("Arcus kernel loaded!", 0);
	print_ak("Arcus OS is loading...", 1);
	enable_cursor(4,5);

	// Sets up IDT
    static struct IdtEntry idt[256];
    static struct Idtr idtr;

    // Zero the table (primitive way)
    for (int i=0;i<256;i++){
        idt[i].off_lo=idt[i].sel=idt[i].zero=idt[i].type_attr=idt[i].off_hi=0;
    }

    // Set vector 0x80 only
    idt_set(idt, 0x80, isr80_stub);

    idtr.limit = sizeof(idt) - 1;
    idtr.base  = (uint32_t)idt;
    lidt(&idtr);

	// Triggering interrupt 0x80
	//__asm__ __volatile__("int $0x80");

	// Starts at caps
	uint8_t *caps_ptr = (uint8_t *)CAPS_BUFF;
	caps_ptr[0] = 0x01;

	print_ak("input \"SELAH\":", 2);
	get_input(test_input, 14, true, 2, 14); 

	if (comp_str_p(test_input, "SELAH")) {print_ak("that is right!", 3);}
	else {print_ak("nope!", 3);}
	print_ak("done!", 4);
}

