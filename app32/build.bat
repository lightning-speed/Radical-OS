cd Shell
call make.bat
cd ../
cd Run
call make.bat
cd ../
cd Editor
call make.bat
cd ../
copy Shell\shell.bin+Run\run.bin+Editor\editor.bin ..\files\apps
pause
s
