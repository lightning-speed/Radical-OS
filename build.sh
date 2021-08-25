mkdir bin
mkdir temp
sed 's/_kmain/kmain/' src/kernel_loader.asm | tee temp/kernel_loader.asm
nasm -f elf32 temp/kernel_loader.asm -o kernel_loader.o
rm -rf temp
gcc -m32 -c -I src/. src/kernel.c -o kernel.o
cd bin
gcc -m32 -c -I ../src/. ../src/Drivers/*.c -fno-stack-protector
gcc -m32 -c -I ../src/. ../src/System/*.c -fno-stack-protector 
gcc -m32 -c -I ../src/. ../src/Graphics/*.c -fno-stack-protector 
gcc -m32 -c -I ../src/. ../src/FS/*.c -fno-stack-protector
gcc -m32 -c -I ../src/. ../src/Shell/*.c -fno-stack-protector
gcc -m32 -c -I ../src/. ../src/Mego-Runtime/*.c -fno-stack-protector
gcc -m32 -c -I ../src/. ../src/Terminal-Runtime/*.c -fno-stack-protector
gcc -m32 -c -I ../src/. ../src/Util/*.c -fno-stack-protector
ld -m elf_i386 ../kernel_loader.o ../kernel.o *.o -o kernel.bin -Ttext 0x1000
rm -rf *.o
rm -rf ../*.o
#objcopy -Felf32-i386 kernel.e kernel.bin
rm -rf *.e
qemu-system-x86_64 -kernel kernel.bin
cd ..
rm -rf bin
