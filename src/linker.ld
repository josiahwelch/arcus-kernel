// Josiah Welch
// 8/29/25
// Linker file

// NOTE: heavily influenced by https://github.com/chipsetx/Simple-Kernel-in-C-and-Assembly#

OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS {
	. = 0x100000;
	.text : {*(.text)}
	.data : {*(.data)}
	.bss : {*(.bss)}
}
