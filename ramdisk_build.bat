cd ramdisk
copy ramdisk_header+ramdisk_content+ramdisk_end ramdisk_total
nasm -f elf32 ramdisk_load.asm -o ramdisk.img
pause