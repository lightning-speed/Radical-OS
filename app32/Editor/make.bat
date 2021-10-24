gcc -m32 -c ../../stdlib/program_header.c -o header.o
gcc -m32 -c editor.c -o editor.o -I ../../stdlib/.
ld -Ttext 0xAAAAAF header.o editor.o -o editor.pe
objcopy -Obinary editor.pe editor.bin
pause