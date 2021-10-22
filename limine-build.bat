tools\mklimine bin\radical.iso limine\ limine.cfg:limine.cfg bin\core.elf:kernel.elf
qemu-system-x86_64.exe bin\radical.iso
pause
