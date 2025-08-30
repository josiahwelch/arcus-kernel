// Josiah Welch
// 8/29/25
// Kernel c file

//NOTE: heavily influenced by https://github.com/chipsetx/Simple-Kernel-in-C-and-Assembly#

//#include "ps2_ak.h"
#include "keyboard.c"

#define COLOR_SCHEME 0x07 // light gray bg with black fg
#define LINE_BUFF 0xFFEE00 // Used to create a line to be printed

int print_ak(char *msg, unsigned int line) {
	char *mem = (char *) 0xb8000;
	unsigned int i = (line * 80 * 2);

	while (*msg != 0) {
		if (*msg == '\n') {
			line++; // Since newline goes to the next line...
			i = (line * 80 * 2);
			*msg++;
		} else {
			mem[i] = *msg;
			*msg++;
			i++;
			mem[i] = COLOR_SCHEME;
			i++;
		}
	}

	return 1;
}

void clear_ak() {
	char *mem = (char *) 0xb8000;
	unsigned int i = 0;
	while (i < (80 * 2 * 25)) {
		mem[i] = ' ';
		i++;
		mem[i] = COLOR_SCHEME;
		i++;
	}
}

void main_ak() {
	clear_ak();
	print_ak("Arca kernel loaded!", 0);
	print_ak("Arca OS is loading...", 1);
	//keyboard_init();
	//print_ak(get_char_from_ps2(), 2);
	char *msg = (char *)0xFFEE00;
	int i = 0;
	msg = "        \0";
	char key = ' ';
	while (1) {
		if (i > 7) {i = 0;}
		switch(get_key()) {
			case KEY_A_PRESSED:
				key = 'A';
				break;
			case KEY_B_PRESSED:
				key = 'B';
				break;
		}
		msg[i] = key;
		print_ak(msg, 2);
		i++;
	}

	if (get_key() == KEY_1_PRESSED) {
		print_ak("1 key pressed!", 2);
	}
}
