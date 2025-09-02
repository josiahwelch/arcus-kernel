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
#include "task_mgr.h"

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
