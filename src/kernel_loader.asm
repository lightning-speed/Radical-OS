bits 32
  dd 0x1BADB002
  dd 0x0
  dd - 0x1BADB002

extern _kmain
  cli
  call _kmain
  jmp $

global _load_idt

_load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti 				;turn on interrupts
	ret