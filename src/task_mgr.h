typedef struct {
	unsigned int esp; // Stack pointer
	unsigned int eip; // Instruction pointer
	// Add other registers if needed (eax, ebx, etc.)
} Task;

Task tasks[2]; // Example: two tasks
int current_task = 0;
