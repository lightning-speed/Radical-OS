#pragma once
#define MASTER_PIC_CMD_PORT 0x20
#define MASTER_PIC_DATA_PORT 0x21
#define SLAVE_PIC_CMD_PORT 0xA0
#define SLAVE_PIC_DATA_PORT 0xA1

#define END_OF_INTERRUPT 0x20
struct idt_entry
{
 unsigned short base_lo;
 unsigned short sel;    /* Our kernel segment goes here! */
 unsigned char always0; /* This will ALWAYS be set to 0! */
 unsigned char flags;   /* Set using the above table! */
 unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
 unsigned short limit;
 unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;
void idt_set_gate(char vector, void *isr, char flags);
void idt_install();
