// Josiah Welch
// 8/30/25
// Utility c file
#ifndef KERN_UTILS_AK_H
#define KERN_UTILS_AK_H
#include "define.h"

static inline void outb(unsigned short port, unsigned char val) {
	asm volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

void io_wait(void) {
	outb(0x80, 0);
}

void cvtostr(char *str, char char_input) {
	int digit1 = 0;
	int digit2 = 0;
	int digit3 = 0;
	unsigned char chr = char_input;

	while (1) {
		if (chr > 99) {
			digit1++;
			chr -= 100;
		}else if (chr > 9) {
			digit2++;
			chr -= 10;
		} else {
			digit3 = chr;
			break;
		}
	}

	str[0] = digit1 + 48;
	str[1] = digit2 + 48;
	str[2] = digit3 + 48;
	str[3] = '\0';
}

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

char get_prev_key() {
	char *ptr = (char *)CHAR_BUFF; 	// Gets the previous char code from buffer
	char prev_key_c = ptr[0]; 		// Gets the first byte at the address 0xFFEDFF
	return prev_key_c;
}

char get_ascii_char() {
	char key_c = get_key();
	char prev_key_c = get_prev_key();
	char *caps_ptr = (char *)CAPS_BUFF;

	unsigned int capital = (caps_ptr[0] == 0x01);

	char key;
	switch (key_c) {
		case KEY_A_PRESSED:
			key = 'A';
			if (!capital) {key = 'a';}
			break;

		case KEY_B_PRESSED:
			key = 'B';
			if (!capital) {key = 'b';}
			break;

		case KEY_C_PRESSED:
			key = 'C';
			if (!capital) {key = 'c';}
			break;

		case KEY_D_PRESSED:
			key = 'D';
			if (!capital) {key = 'd';}
			break;

		case KEY_E_PRESSED:
			key = 'E';
			if (!capital) {key = 'e';}
			break;

		case KEY_F_PRESSED:
			key = 'F';
			if (!capital) {key = 'f';}
			break;

		case KEY_G_PRESSED:
			key = 'G';
			if (!capital) {key = 'g';}
			break;

		case KEY_H_PRESSED:
			key = 'H';
			if (!capital) {key = 'h';}
			break;

		case KEY_I_PRESSED:
			key = 'I';
			if (!capital) {key = 'i';}
			break;

		case KEY_J_PRESSED:
			key = 'J';
			if (!capital) {key = 'j';}
			break;

		case KEY_K_PRESSED:
			key = 'K';
			if (!capital) {key = 'k';}
			break;

		case KEY_L_PRESSED:
			key = 'L';
			if (!capital) {key = 'l';}
			break;

		case KEY_M_PRESSED:
			key = 'M';
			if (!capital) {key = 'm';}
			break;

		case KEY_N_PRESSED:
			key = 'N';
			if (!capital) {key = 'n';}
			break;

		case KEY_O_PRESSED:
			key = 'O';
			if (!capital) {key = 'o';}
			break;

		case KEY_P_PRESSED:
			key = 'P';
			if (!capital) {key = 'p';}
			break;

		case KEY_Q_PRESSED:
			key = 'Q';
			if (!capital) {key = 'q';}
			break;

		case KEY_R_PRESSED:
			key = 'R';
			if (!capital) {key = 'r';}
			break;

		case KEY_S_PRESSED:
			key = 'S';
			if (!capital) {key = 's';}
			break;

		case KEY_T_PRESSED:
			key = 'T';
			if (!capital) {key = 't';}
			break;

		case KEY_U_PRESSED:
			key = 'U';
			if (!capital) {key = 'u';}
			break;

		case KEY_V_PRESSED:
			key = 'V';
			if (!capital) {key = 'v';}
			break;

		case KEY_W_PRESSED:
			key = 'W';
			if (!capital) {key = 'w';}
			break;

		case KEY_X_PRESSED:
			key = 'X';
			if (!capital) {key = 'x';}
			break;

		case KEY_Y_PRESSED:
			key = 'Y';
			if (!capital) {key = 'y';}
			break;

		case KEY_Z_PRESSED:
			key = 'Z';
			if (!capital) {key = 'z';}
			break;
		default:
			key = '\0';
			break;
	}
	return key;
}

void enable_cursor(unsigned char cursor_start, unsigned char cursor_end)
{
		outb(0x3D4, 0x0A);
		outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

		outb(0x3D4, 0x0B);
		outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor()
{
		outb(0x3D4, 0x0A);
			outb(0x3D5, 0x20);
}

void update_cursor(unsigned char x, unsigned char y)
{
	unsigned short pos = y * VGA_WIDTH + x;

	unsigned char *x_ptr = (unsigned char *)CURSOR_POS_X;
	unsigned char *y_ptr = (unsigned char *)CURSOR_POS_Y;

	x_ptr[0] = x;
	y_ptr[0] = y;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
}

void move_cursor_up() {
	unsigned char *x_ptr = (unsigned char *)CURSOR_POS_X;
	unsigned char *y_ptr = (unsigned char *)CURSOR_POS_Y;
	if (y_ptr[0] > 0) {y_ptr[0]--;}
	update_cursor(x_ptr[0], y_ptr[0]);
}

#endif KERN_UTILS_AK_H
