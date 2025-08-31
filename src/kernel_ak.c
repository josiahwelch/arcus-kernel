// Josiah Welch
// 8/29/25
// Kernel c file

//NOTE: heavily influenced by https://github.com/chipsetx/Simple-Kernel-in-C-and-Assembly#

//#include "ps2_ak.h"
#include "keyboard.c"
#include "kern_utils_ak.h"

#define COLOR_SCHEME 0x08 	// light gray bg with black fg
#define LINE_BUFF 0x00EE00 	// Used to create a line to be printed
#define CHAR_BUFF 0x00EDFF 	// Used to store last char
#define SHIFT_BUFF 0x00EDF0	// Used to indicate if shift is activated 
#define CAPS_BUFF 0x00EDE0	// Used to indicate if CapsLock is active

void main_ak() {
	clear_ak();
	print_ak("Arcus kernel loaded!", 0);
	print_ak("Arcus OS is loading...", 1);
	enable_cursor(0, 15);
	char *msg = (char *)0xFFEE00;
	int i = 0;
	msg = "        \0";
	while (1) {
		if (i > 7) {i = 0;}
		msg[i] = get_ascii_char();
		print_ak(msg, 2);
		update_cursor(i, 2);
		i++;
	}

	if (get_key() == KEY_1_PRESSED) {
		print_ak("1 key pressed!", 2);
	}
}
