mkdir bin
del bin\*.o
nasm -f elf32 src\kernel_loader.asm -o kernel_loader.o
nasm -f elf32 src\Drivers\gdt.asm -o bin\int.o
i686-elf-gcc   -std=gnu99 -m32 -c -I src\. src\kernel.c -o kernel.o
cd bin
i686-elf-gcc  -std=gnu99 -m32 -c -I ..\src\. ..\src\Drivers\*.c 
i686-elf-gcc  -std=gnu99 -m32 -c -I ..\src\. ..\src\System\*.c 
i686-elf-gcc  -std=gnu99 -m32 -c -I ..\src\. ..\src\Graphics\*.c
i686-elf-gcc  -std=gnu99 -m32 -c -I ..\src\. ..\src\Timer\*.c 
i686-elf-gcc  -std=gnu99 -m32 -c -I ..\src\. ..\src\FS\*.c 
i686-elf-gcc  -std=gnu99 -m32 -c -I ..\src\. ..\src\Util\*.c 
ld ..\kernel_loader.o ..\kernel.o  *.o ..\ramdisk\ramdisk.img  -o kernel.e
del ..\*.o
del *.o
objcopy -Felf32-i386 kernel.e core.elf
del *.e
qemu-system-x86_64.exe -kernel core.elf
cd ..
pause
