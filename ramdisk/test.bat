gcc -m32 -c test.c
custom-ld --oformat binary -Ttext 0xAAAAAF test.o -o ramdisk_content
pause