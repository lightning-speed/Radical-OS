cd Shell
call make.bat
cd ../
cd Editor
call make.bat
cd ../
cd Calculator
call make.bat
cd ../
cd Stopwatch
call make.bat
cd ../
copy Shell\shell.bin+Editor\editor.bin+Calculator\calc.bin+Stopwatch\sw.bin ..\files\apps
pause

