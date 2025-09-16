// Josiah Welch
// 8/29/25
// Kernel c file

#include "define.h"
#include <stdint.h>
#include <stdbool.h>
#include "io_ak.h"
#include "keyboard.c"
#include "kern_utils_ak.h"

char *test_input[16];

void main_ak(void){
	clear_ak();
	print_ak("Arcus kernel loaded!", 0);
	print_ak("Arcus OS is loading...", 1);
	enable_cursor(4,5);

	// Starts at caps
	uint8_t *caps_ptr = (uint8_t *)CAPS_BUFF;
	caps_ptr[0] = 0x01;

	print_ak("input \"SELAH\":", 2);
	get_input(test_input, 14, true, 2, 14); 

	if (comp_str_p(test_input, "SELAH")) {print_ak("that is right!", 3);}
	else {print_ak("nope!", 3);}
	print_ak("done!", 4);

}

