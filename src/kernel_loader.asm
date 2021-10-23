bits 32
  dd 0x1BADB002
  dd 0x0
  dd - 0x1BADB002

extern kmain
global _start
_start:
  cli
  call kmain
  jmp $
