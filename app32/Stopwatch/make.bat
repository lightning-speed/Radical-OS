gcc -m32 -c ../../stdlib/program_header.c -o header.o
gcc -m32 -c sw.c -o sw.o -I ../../stdlib/.
ld -Ttext 0xAAAAAF header.o sw.o -o sw.pe
objcopy -Obinary sw.pe sw.bin
pause