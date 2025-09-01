#define COLOR_SCHEME 0x07 		// light gray bg with black fg
#define LINE_BUFF 0x00EE00 		// Used to create a line to be printed
#define CHAR_BUFF 0x00EDFF 		// Used to store last char
#define SHIFT_BUFF 0x00EDF0		// Used to indicate if shift is activated 
#define CAPS_BUFF 0x00EDE0		// Used to indicate if CapsLock is active
#define CURSOR_POS_Y 0x00EDDA	// Stores the y value of the cursor position 
#define CURSOR_POS_X 0x00EDD0	// Stores the x value of the cursor position 
#define VGA_WIDTH 80 			// Width of the screen in characters
#define IDT_MAX_DESCRIPTORS 0	// Stores number of entries in IDT
