// Josiah Welch
// 8/30/25
// Utility c file
#ifndef KERN_UTILS_AK_H
#define KERN_UTILS_AK_H

/*
void cvtostr(char *str, char char_input) {
	int digit1 = 0;
	int digit2 = 0;
	int digit3 = 0;
	unsigned char chr = char_input;

	while (digit3 != chr) {
		if (chr > 99) {
			digit1++;
			chr -= 100;
		}else if (chr > 9) {
			digit2++;
			chr -= 10;
		} else {
			digit3 = chr;
		}
	}

	str[0] = digit1 + 48;
	str[1] = digit2 + 48;
	str[2] = digit3 + 48;
	str[3] = '\0';
}
*/

void cvtostr(char *str, char char_input) {
	int digit1 = 0;
	int digit2 = 0;
	unsigned char chr = char_input;

	while (digit2 != chr) {
		if (chr > 9) {
			digit1++;
			chr -= 10;
		} else {
			digit2 = chr;
		}
	}

	str[0] = digit1 + 48;
	str[1] = digit2 + 48;
	str[2] = '\0';
}

int print_col_ak(char *msg, unsigned int line, unsigned int color) {
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
			mem[i] = color;
			i++;
		}
	}
return 1;
}

int print_row_ak(char *msg, unsigned int line, unsigned int row) {
	char *mem = (char *) 0xb8000;
	unsigned int i = (line * 80 * 2) + row * 2;

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

void print_ak_buff(unsigned int line) {
	char *msg = (char *)LINE_BUFF;
	print_ak(msg, line);
}

char get_prev_key() {
	char *ptr = (char *)CHAR_BUFF; 	// Gets the previous char code from buffer
	char prev_key_c = ptr[0]; 		// Gets the first byte at the address 0xFFEDFF
	return prev_key_c;
}

char key_presses_enums[] = {KEY_A_PRESSED, KEY_B_PRESSED, KEY_C_PRESSED, KEY_D_PRESSED, KEY_E_PRESSED, KEY_F_PRESSED, KEY_G_PRESSED, KEY_H_PRESSED, KEY_I_PRESSED, KEY_J_PRESSED, KEY_K_PRESSED, KEY_L_PRESSED, KEY_M_PRESSED, KEY_N_PRESSED, KEY_O_PRESSED, KEY_P_PRESSED, KEY_Q_PRESSED, KEY_R_PRESSED, KEY_S_PRESSED, KEY_T_PRESSED, KEY_U_PRESSED, KEY_V_PRESSED, KEY_W_PRESSED, KEY_X_PRESSED, KEY_Y_PRESSED, KEY_Z_PRESSED, KEY_SPACE_PRESSED};
char upper_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
char lower_chars[] = "abcdefghijklmnopqrstuvwxyz ";

char handle_key_input() {
	char key_c = get_key();
	char prev_key_c = get_prev_key();
	char *caps_ptr = (char *)CAPS_BUFF;

	uint8_t capital = (caps_ptr[0] == 0x01);

	if (key_c == (char)KEY_CAPSLOCK_PRESSED) { 
		return 0x00;
	}
	else if (key_c == KEY_BACKSPACE_PRESSED) {
		return 0x01;
	}
	else if (key_c == KEY_ENTER_PRESSED) {
		return 0x02;
	}
	else {
		for (int i = 0; i < 27; i++) {
			if (key_c == key_presses_enums[i]) {
				if (capital) {return upper_chars[i];}
				else {return lower_chars[i];}
			}
		}
	}
}

void copy_str_p(char *sink, char *src) {
	for (int i = 0; src[i] != '\0'; i++) {
		sink[i] = src[i];
	}
}

bool comp_str_p(char *ptr1, char *ptr2) {
	ptr1 += '\0';
	ptr2 += '\0';
	for (int i = 0; ptr1[i] == ptr2[i]; i++) {
		if (ptr1[i] == '\0') {return true;} // Can only check one char from ptr since both should be same
	}
	return false;
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
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

void update_cursor(int x, int y)
{
	uint16_t pos = (y + 1) * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}
uint16_t get_cursor_position(void)
{
	uint16_t pos = 0;
	outb(0x3D4, 0x0F);
	pos |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	pos |= ((uint16_t)inb(0x3D5)) << 8;
	return pos;
}

// Yes, I know that this is ugly
void get_input(char *inp_ptr, unsigned int length, bool echo, unsigned int c_row, unsigned int c_col) {
	char *vid_mem = (char *) 0xb8000;
	char *inp_mem = (char *) INPUT_BUFF;

	unsigned int c_start = (c_row * 80 * 2 + 2 * c_col);
	int i = 0;
	char key_c = 0x01;
	char key = ' ';
	enable_cursor(0,0);

	while (key_c != 0x02) {
		for (i; i < length && i >= -1; i++) {
			key_c = handle_key_input();
			if (key_c == 0x00) {
				if (i > 0) {i--;}
			}
			else if (key_c == 0x01) {
				if (i > 0) {i--;}
				key = ' ';
			}
			else if (key_c == 0x02) {
				copy_str_p(inp_ptr, inp_mem);
				return;
			}
			else {key = key_c;}

			inp_mem[i] = key;
			if (echo) {
				vid_mem[c_start + 2 * i]  = key;
				vid_mem[c_start + 2 * i + 1] = COLOR_SCHEME;
				update_cursor(c_col + i, c_row);
			}
			if (key_c == 0x00 && i == 0) {i--;}
			if (key_c == 0x01 && i >= 0) {i--;}
		}
		if (i > length) {i = length;}
		else if (i < 0) {i = 0;}
		if (handle_key_input() == 0x01) {
			vid_mem[c_start + 2 * i - 2] = ' ';
			if (i > 0) {i--;}
		} 
	}
}

#endif KERN_UTILS_AK_H
