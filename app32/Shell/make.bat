gcc -m32 -c shell.c -o shell.o
custom-ld -Ttext 0xAAAAAF shell.o -o shell.bin --oformat binary
pause