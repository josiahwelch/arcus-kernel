__attribute__((interrupt))
void keyboard_handler(void* frame) {
	uint8_t scancode = inb(0x60);
	(void)frame; // unused

	// For testing: ignore scancode
	pic_eoi(1);
}
