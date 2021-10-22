cd Shell
call make.bat
cd ../
cd Run
call make.bat
cd ../
copy Shell\shell.bin+Run\run.bin ..\files\apps
pause
s
