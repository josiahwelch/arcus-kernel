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

	while (1) {
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
	}

	str[0] = digit1 + 48;
	str[1] = digit2 + 48;
	str[2] = digit3 + 48;
	str[3] = '\0';
}
*/

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

uint16_t key_presses_enums[] = {KEY_A_PRESSED, KEY_B_PRESSED, KEY_C_PRESSED, KEY_D_PRESSED, KEY_E_PRESSED, KEY_F_PRESSED, KEY_G_PRESSED, KEY_H_PRESSED, KEY_I_PRESSED, KEY_J_PRESSED, KEY_K_PRESSED, KEY_L_PRESSED, KEY_M_PRESSED, KEY_N_PRESSED, KEY_O_PRESSED, KEY_P_PRESSED, KEY_Q_PRESSED, KEY_R_PRESSED, KEY_S_PRESSED, KEY_T_PRESSED, KEY_U_PRESSED, KEY_V_PRESSED, KEY_W_PRESSED, KEY_X_PRESSED, KEY_Y_PRESSED, KEY_Z_PRESSED, KEY_SPACE_PRESSED, /*start of non-regular*/ KEY_CAPSLOCK_PRESSED, KEY_LEFT_SHIFT_PRESSED, KEY_RIGHT_SHIFT_PRESSED};

char key_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
char lower_key_chars[] = "abcdefghijklmnopqrstuvwxyz ";
// start of non-regular

char handle_key_input() {
	char key_c = get_key();
	char prev_key_c = get_prev_key();
	uint8_t *caps_ptr = (uint8_t *)CAPS_BUFF;
	uint8_t capital = (caps_ptr[0] == 0x01);

	char key = 0x00;
	if (key_c == KEY_CAPSLOCK_PRESSED || key_c == KEY_LEFT_SHIFT_PRESSED || key_c == KEY_RIGHT_SHIFT_PRESSED) { 
		if (caps_ptr[0] == 0x00) {caps_ptr[0] = 0x01;}
		else {caps_ptr[0] = 0x00;}
		return 0x00;
	}
	else if (key_c == KEY_BACKSPACE_PRESSED) {
		return 0x01;
	}
	else if (key_c == KEY_ENTER_PRESSED) {
		return 0x02;
	}

	for (int i = 0; i < 27; i++) {
		if (key_c == key_presses_enums[i]) {
			if (capital) {key = key_chars[i];}
			else {key = lower_key_chars[i];}
		}
	}
	return key;
}

void print_ak_buff(unsigned int line) {
	char *msg = (char *)LINE_BUFF;
	print_ak(msg, line);
}

void get_input(char *in_ptr, unsigned int length, bool echo, unsigned int c_row, unsigned int c_col) {

	char *vid_mem = (char *) 0xb8000;
	char *inp_mem = (char *) 0x00ed00;

	unsigned int c_start = (c_row * 80 * 2 + 2 * c_col);
	int i=0;
	char char_read = 0x00;
	char char_proc = ' ';

	while (char_read != 0x02) {
		for (i; i<length; i++) {
			char_read = handle_key_input();
			if (char_read == 0x00) {i--;} // Ignores CapsLock as key
			else if (char_read == 0x01) { // Sets the char to space
				i--;
				char_proc = ' ';
			}
			else {char_proc = char_read;}
			if(echo) {
				vid_mem[c_start + 2 * i] = char_proc;
				vid_mem[c_start + 2 * i + 1] = COLOR_SCHEME;
			}
			inp_mem[i] = char_read;
			inp_mem[i+1] = '\0';

			if (char_read == 0x02) {
				i = length + 1;
			}
			if (char_read == 0x01) { // Backspace secondary decrement
				i--;
			}
		}
		if (i>=length) {i = length;} // Resets i
		else {i = 0;}
		if (handle_key_input() == 0x01) {
			vid_mem[c_start + 2 * (length - 1)] = ' ';
			i--;
		}
	}
	in_ptr = inp_mem;
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
	uint16_t pos = y * VGA_WIDTH + x;

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

void move_cursor_up() {
	uint8_t *x_ptr = (uint8_t *)CURSOR_POS_X;
	uint8_t *y_ptr = (uint8_t *)CURSOR_POS_Y;

	if (y_ptr[0] > 0) {y_ptr[0]--;}
	update_cursor(x_ptr[0], y_ptr[0]);
}

#endif KERN_UTILS_AK_H
