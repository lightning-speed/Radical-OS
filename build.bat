mkdir bin
del bin\*.o
nasm -f elf32 src\kernel_loader.asm -o kernel_loader.o
nasm -f elf32 src\Drivers\int.asm -o bin\int.o
gcc   -m32 -c -I src\. src\kernel.c -o kernel.o
cd bin
gcc  -m32 -c -I ..\src\. ..\src\Drivers\*.c 
gcc  -m32 -c -I ..\src\. ..\src\System\*.c 
gcc  -m32 -c -I ..\src\. ..\src\Graphics\*.c
gcc  -m32 -c -I ..\src\. ..\src\Timer\*.c 
gcc  -m32 -c -I ..\src\. ..\src\FS\*.c 
gcc  -m32 -c -I ..\src\. ..\src\App32\*.c 
gcc  -m32 -c -I ..\src\. ..\src\Shell\*.c 
gcc  -m32 -c -I ..\src\. ..\src\Mego-Runtime\*.c 
gcc  -m32 -c -I ..\src\. ..\src\Terminal-Runtime\*.c 
gcc  -m32 -c -I ..\src\. ..\src\Util\*.c 
ld ..\kernel_loader.o ..\kernel.o  *.o ..\ramdisk\ramdisk.img  -o kernel.e
del ..\*.o
del *.o
objcopy -Felf32-i386 kernel.e core.elf
del *.e
qemu-system-x86_64.exe -kernel core.elf
cd ..
pause
