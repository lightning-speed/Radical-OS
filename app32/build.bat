cd Shell
call make.bat
cd ../
cd Run
call make.bat
cd ../
copy Shell\shell.bin+..\ramdisk\file_divider+Run\run.bin+..\ramdisk\file_divider ..\ramdisk\ramdisk_content
pause