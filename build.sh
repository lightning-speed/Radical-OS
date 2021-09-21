echo Cleaning
mkdir -p bin
rm -r -f bin/*.o
echo Building
nasm -f elf32 src/kernel_loader2.asm -o kernel_loader.o
gcc -m32 -c -I src/. src/kernel.c -o kernel.o
cd bin
gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I ../src/. ../src/Drivers/*.c 
gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I ../src/. ../src/System/*.c 
gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I ../src/. ../src/Graphics/*.c
gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I ../src/. ../src/Timer/*.c 
gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I ../src/. ../src/FS/*.c 
gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I ../src/. ../src/App32/*.c 
gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I ../src/. ../src/Shell/*.c 
gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I ../src/. ../src/Mego-Runtime/*.c 
gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I ../src/. ../src/Terminal-Runtime/*.c 
gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I ../src/. ../src/Util/*.c 
ld -static -Bsymbolic -nostdlib -m elf_i386 -Ttext 0x100000 ../kernel_loader.o ../kernel.o  *.o  -o kernel.e
rm ../*.o
rm *.o
objcopy -Felf32-i386 kernel.e kernel.elf
rm *.e
qemu-system-x86_64 -kernel kernel.elf
cd ..
rm -r -f bin
echo Done
