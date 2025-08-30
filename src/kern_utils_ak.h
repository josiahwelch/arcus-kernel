#ifndef KERN_UTILS_AK_H
#define KERN_UTILS_AK_H

#define COLOR_SCHEME 0x07 // light gray bg with black fg
#define LINE_BUFF 0xFFEE00 // Used to create a line to be printed
#define CHAR_BUFF 0xFFEDFF // Used to store last char

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

#endif KERN_UTILS_AK_H
