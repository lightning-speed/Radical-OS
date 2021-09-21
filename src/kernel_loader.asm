bits 32
  dd 0x1BADB002
  dd 0x0
  dd - 0x1BADB002

extern _kmain
  cli
  call _kmain
  jmp $


