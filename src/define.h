#define COLOR_SCHEME 0x07 		// light gray bg with black fg
#define LINE_BUFF 0x00EE00 		// Used to create a line to be printed
#define CHAR_BUFF 0x00EDFF 		// Used to store last char
#define SHIFT_BUFF 0x00EDF0		// Used to indicate if shift is activated 
#define CAPS_BUFF 0x00EDE0		// Used to indicate if CapsLock is active
#define INPUT_BUFF 0x00ED00		// Stores characters read from input
#define CURSOR_POS_Y 0x00EDDA	// Stores the y value of the cursor position 
#define CURSOR_POS_X 0x00EDD0	// Stores the x value of the cursor position 
#define VGA_WIDTH 80 			// Width of the screen in characters
#define IDT_MAX_DESCRIPTORS 1 	// Number of entries in IDT

// PIC stuff
#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
