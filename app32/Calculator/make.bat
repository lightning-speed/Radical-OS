gcc -m32 -c ../../stdlib/program_header.c -o header.o
gcc -m32 -c calc.c -o calc.o -I ../../stdlib/.
ld -Ttext 0xAAAAAF header.o calc.o -o calc.pe
objcopy -Obinary calc.pe calc.bin
pause