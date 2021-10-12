mkdir bin
del bin\*.o
nasm -f elf32 src\kernel_loader.asm -o kernel_loader.o
nasm -f elf32 src\Drivers\gdt.asm -o gdt.o
i686-elf-gcc -std=gnu99   -m32 -c -I src\. src\kernel.c -o kernel.o
cd bin
i686-elf-gcc -std=gnu99  -m32 -c -I ..\src\. ..\src\Drivers\*.c 
i686-elf-gcc -std=gnu99  -m32 -c -I ..\src\. ..\src\System\*.c 
i686-elf-gcc -std=gnu99  -m32 -c -I ..\src\. ..\src\Graphics\*.c
i686-elf-gcc -std=gnu99  -m32 -c -I ..\src\. ..\src\Timer\*.c 
i686-elf-gcc -std=gnu99  -m32 -c -I ..\src\. ..\src\FS\*.c 
i686-elf-gcc -std=gnu99  -m32 -c -I ..\src\. ..\src\App32\*.c 
i686-elf-gcc -std=gnu99  -m32 -c -I ..\src\. ..\src\Shell\*.c 
i686-elf-gcc -std=gnu99  -m32 -c -I ..\src\. ..\src\Mego-Runtime\*.c 
i686-elf-gcc -std=gnu99  -m32 -c -I ..\src\. ..\src\Terminal-Runtime\*.c 
i686-elf-gcc -std=gnu99  -m32 -c -I ..\src\. ..\src\Util\*.c 
i686-elf-ld -m elf_i386 -Ttext 0xC00000 ..\kernel_loader.o ..\kernel.o ..\gdt.o  *.o ..\ramdisk\ramdisk.img  -o core.elf
del ..\*.o
del *.o
del *.e
qemu-system-x86_64.exe -kernel core.elf
cd ..
pause
