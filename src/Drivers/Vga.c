#include <stdint.h>
#include <System/IO.h>
#define VGA_BLACK 0x00
#define VGA_BLUE 0x01
#define VGA_GREEN 0x02
#define VGA_CYAN 0x03
#define VGA_RED 0x04
#define VGA_MAGENTA 0x05
#define VGA_BROWN 0x06
#define VGA_LIGHTGRAY 0x07
#define VGA_DARKGRAY 0x08
#define VGA_LIGHTBLUE 0x09
#define VGA_LIGHTGREEN 0x0A
#define VGA_LIGHTCYAN 0x0B
#define VGA_LIGHTRED 0x0C
#define VGA_LIGHTMAGENTA 0x0D
#define VGA_YELLOW 0x0E
#define VGA_WHITE 0x0F

#define MISC_PORT 0x3c2
#define CRTC_INDEX_PORT 0x3d4
#define CRTC_DATA_PORT 0x3d5
#define SEQUENCER_INDEX_PORT 0x3c4
#define SEQUENCER_DATA_PORT 0x3c5
#define GRAPHICS_CONTROLLER_INDEX_PORT 0x3ce
#define GRAPHICS_CONTROLLER_DATA_PORT 0x3cf
#define ATTRIBUTE_CONTROLLER_INDEX_PORT 0x3c0
#define ATTRIBUTE_CONTROLLER_READ_PORT 0x3c1
#define ATTRIBUTE_CONTROLLER_WRITE_PORT 0x3c0
#define ATTRIBUTE_CONTROLLER_RESET_PORT 0x3da

void init_vga();

void setpixel(int x, int y, uint32_t color);
unsigned char getpixel(int x, int y);
volatile void draw_char(char c, int x, int y);
void clear_vga();
void vga_kputc(char c);
void vga_kputs(const char *s);
void set_vga_color(uint32_t fgcolor, uint32_t bgcolor);
int is_vga_active();

const int LSB[0][0] = {};
unsigned char g_80x25_text[] =
				{
								/* MISC */
								0x67,
								/* SEQ */
								0x03, 0x00, 0x03, 0x00, 0x02,
								/* CRTC */
								0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
								0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x50,
								0x9C, 0x0E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
								0xFF,
								/* GC */
								0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
								0xFF,
								/* AC */
								0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
								0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
								0x0C, 0x00, 0x0F, 0x08, 0x00};
unsigned char g_320x200x256[] = {
				/* MISC */
				0x63,
				/* SEQ */
				0x03, 0x01, 0x0F, 0x00, 0x0E,
				/* CRTC */
				0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
				0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
				0xFF,
				/* GC */
				0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
				0xFF,
				/* AC */
				0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
				0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
				0x41, 0x00, 0x0F, 0x00, 0x00};

unsigned char *VGA = (unsigned char *)0xA0000;
int vga_x = 0;
int vga_y = 0;

int vga_active = 0;

uint32_t vga_fgcolor = VGA_WHITE;
uint32_t vga_bgcolor = VGA_BLACK;

void vga_write_registers(uint8_t *regs)
{
 outportb(MISC_PORT, *(regs++));

 for (uint8_t i = 0; i < 5; i++)
 {
		outportb(SEQUENCER_INDEX_PORT, i);
		outportb(SEQUENCER_DATA_PORT, *(regs++));
 }

 outportb(CRTC_INDEX_PORT, 0x03);
 outportb(CRTC_DATA_PORT, inportb(CRTC_DATA_PORT) | 0x80);
 outportb(CRTC_INDEX_PORT, 0x11);
 outportb(CRTC_DATA_PORT, inportb(CRTC_DATA_PORT) & ~0x80);

 regs[0x03] = regs[0x03] | 0x80;
 regs[0x11] = regs[0x11] & ~0x80;

 for (uint8_t i = 0; i < 25; i++)
 {
		outportb(CRTC_INDEX_PORT, i);
		outportb(CRTC_DATA_PORT, *(regs++));
 }

 for (uint8_t i = 0; i < 9; i++)
 {
		outportb(GRAPHICS_CONTROLLER_INDEX_PORT, i);
		outportb(GRAPHICS_CONTROLLER_DATA_PORT, *(regs++));
 }

 for (uint8_t i = 0; i < 21; i++)
 {
		inportb(ATTRIBUTE_CONTROLLER_RESET_PORT);
		outportb(ATTRIBUTE_CONTROLLER_INDEX_PORT, i);
		outportb(ATTRIBUTE_CONTROLLER_WRITE_PORT, *(regs++));
 }

 inportb(ATTRIBUTE_CONTROLLER_RESET_PORT);
 outportb(ATTRIBUTE_CONTROLLER_INDEX_PORT, 0x20);
}

unsigned char *get_framebuffer()
{
 outportb(GRAPHICS_CONTROLLER_INDEX_PORT, 0x06);
 uint8_t segment_number = inportb(GRAPHICS_CONTROLLER_DATA_PORT) & (3 << 2);

 switch (segment_number)
 {
 case 0 << 2:
		return (unsigned char *)0x00000;
 case 1 << 2:
		return (unsigned char *)0xa0000;
 case 2 << 2:
		return (unsigned char *)0xb0000;
 case 3 << 2:
		return (unsigned char *)0xb8000;
 default:
		return 0;
 }
}

void init_vga()
{

 vga_write_registers(g_320x200x256);
 VGA = get_framebuffer();

 clear_vga();

 vga_active = 1;
}
void disable_vga()
{
 vga_write_registers(g_80x25_text);
 vga_active = 0;
}

int is_vga_active()
{
 return vga_active;
}

void setpixel(int x, int y, uint32_t color)
{
 int offset;
 if (0 <= x && x < 320)
 {
		if (0 <= y && y < 200)
		{
			offset = 320 * y + x;
			VGA[offset] = color;
		}
 }
}

unsigned char getpixel(int x, int y)
{
 int offset;
 if (0 <= x && x < 320)
 {
		if (0 <= y && y < 200)
		{
			offset = 320 * y + x;
			return VGA[offset];
		}
 }
 return 0;
}

void clear_vga()
{
 for (int x = 0; x < 320; x++)
 {
		for (int y = 0; y < 200; y++)
		{
			setpixel(x, y, vga_bgcolor);
		}
 }
 vga_x = 0;
 vga_y = 0;
}
