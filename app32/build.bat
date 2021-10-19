cd Shell
call make.bat
cd ../
copy Shell\shell.bin+..\ramdisk\file_divider ..\ramdisk\ramdisk_content
copy Shell\shell.bin+..\ramdisk\file_divider ..\ramdisk\ramdisk_content

pause