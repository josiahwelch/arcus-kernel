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
    __asm__ __volatile__(
        "pushad\n\t"              // save EAX..EDI
        // write a visible char to VGA directly (no C call needed)
        "mov eax, 0xB8000\n\t"
        "mov dx, 0x0741\n\t"      // 'A' with light gray attr
        "mov [eax], dx\n\t"       // drop at top-left; simple proof
        "popad\n\t"
        "add esp, 4\n\t"          // drop pushed vector
        "iret\n\t"
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

	// Starts at caps
	uint8_t *caps_ptr = (uint8_t *)CAPS_BUFF;
	caps_ptr[0] = 0x01;

	print_ak("input \"HELLO\":", 2);
	get_input(test_input, 14, true, 2, 14); 

	if (comp_str_p(test_input, "HELLO")) {print_ak("that is right!", 3);}
	else {print_ak("nope!", 3);}
	print_ak("done!", 4);

}

