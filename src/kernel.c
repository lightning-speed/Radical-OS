#include <Drivers/Screen.h>
#include <Drivers/Keyboard.h>
#include <System/SystemTime.h>
#include <Graphics/Graphics.h>
#include <FS/vfs.h>
#include <System/BinaryRuntime.h>
#include <Util/string.h>
#include <Drivers/gdt.h>
#include <Drivers/idt.h>
#include <Timer/Timer.h>
#include <System/IO.h>
#include <System/MemoryManager.h>
#include <Drivers/ramdisk.h>
#include <System/sys_call.h>
#include <Timer/Scheduler.h>
void sys_call(void);
void init_pic(void)
{
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xA1, 0x70);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);
}
void start_everything();
int kmain()
{
	time_init();
	screen_init();
	clearFullScreen();
	gdt_install();
	idt_install();
	init_pic();
	idt_set_gate(33, keyboard_handler, 0x8E);
	idt_set_gate(32, timer_handler, 0x8E);
	asm("sti");
	Screen->cursorY = 5;
	printCenter(5, "OOOOOO ", 0x0e);
	printCenter(6, "O     O", 0x0d);
	printCenter(7, "O     O", 0x0c);
	printCenter(8, "OOOOOO ", 0x0b);
	printCenter(9, "O   O  ", 0x0a);
	printCenter(10, "O    O ", 0x09);
	printCenter(11, "O     O", 0x08);
	printCenter(5, "OOOOOO ", 0x0e);
	printCenter(6, "O     O", 0x0d);
	printCenter(7, "O     O", 0x0c);
	printCenter(8, "OOOOOO ", 0x0b);
	printCenter(9, "O   O  ", 0x0a);
	printCenter(10, "O    O ", 0x09);
	printCenter(11, "O     O", 0x08);
	for (int i = 0; i < 12 * 160; i += 2)
	{
		if (Screen->vga[i] == 'O')
			Screen->vga[i] = 2;
	}
	printCenter(16, " Radical OS", 0x0f);
	setCursorPosition(-1, -1);
	printCenter(14, " .         ", 0x0f);
	Sleep(700);
	printCenter(14, " .  .      ", 0x0f);
	Sleep(700);
	printCenter(14, " .  .  .   ", 0x0f);
	Sleep(700);
	printCenter(14, " .  .  .  .", 0x0f);
	Sleep(700);
	clearScreen();
	start_everything();
	for (;;)
	{
	}
	return 0;
}
void start_everything()
{
	print("--------------------------------------------------------", 0x0e);
	print("\n|                 Welcome to Radical OS                |", 0x0e);
	print("\n--------------------------------------------------------", 0x0e);
	print("\n\nKernel: ", 0x0a);
	print("radical kernel\n", 0x0b);
	print("Version: ", 0x0a);
	print("3.6.0\n\n", 0x05);
	print("Setting Up Memory Manager...", 0x0f);
	memory_init();
	print("  [ Done ]\n", 0x0A);
	print("Setting Up VFS...           ", 0x0f);
	init_fs();
	print("  [ Done ]\n", 0x0C);
	print("Loading Ram Disk...         ", 0x0f);
	load_ramdisk();
	print("  [ Done ]\n", 0x0D);
	print("Creating Files...           ", 0x0f);
	create_file_from_ramdisk();
	print("  [ Done ]\n", 0x0E);
	setup_call_handler();
	binary_runtime_init();
	run_binary_file("shell.bin");
	printW("\nNo more execution left. System Halted!");
}
