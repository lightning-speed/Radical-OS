gcc -m32 -c ../../stdlib/program_header.c -o header.o
gcc -m32 -c run.c -o run.o -I ../../stdlib/.
ld -Ttext 0xAAAAAF header.o run.o -o run.pe
objcopy -Obinary run.pe run.binf
copy name+run.binf run.bin
pause