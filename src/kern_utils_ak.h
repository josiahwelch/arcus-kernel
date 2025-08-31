#ifndef KERN_UTILS_AK_H
#define KERN_UTILS_AK_H

#define COLOR_SCHEME 0x07 	// light gray bg with black fg
#define LINE_BUFF 0xFFEE00 	// Used to create a line to be printed
#define CHAR_BUFF 0xFFEDFF 	// Used to store last char
#define SHIFT_BUFF 0xFFEDFE	// Used to indicate if shift is activated 

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

char get_ascii_char() {
	char *prev_ptr = (char *)CHAR_BUFF; // Gets the previous char code from buffer
	char prev_key_c = prev_ptr[0]; // Gets the first byte at the address 0xFFEDFF
	int capital = (prev_key_c == KEY_LEFT_SHIFT_PRESSED | prev_key_c == KEY_RIGHT_SHIFT_PRESSED);
	char key_c = get_key();
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

#endif KERN_UTILS_AK_H
