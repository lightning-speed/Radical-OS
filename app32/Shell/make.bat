gcc -m32 -c ../../stdlib/program_header.c -o header.o
gcc -m32 -c shell.c -o shell.o -I ../../stdlib/.
ld -Ttext 0xAAAAAF header.o shell.o -o shell.pe
objcopy -Obinary shell.pe shell.bin
pause
