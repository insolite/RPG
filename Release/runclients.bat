echo off
cls
set /a i=0
:loop
if %i%==200 goto end
start Client.exe
set /a i+=1
goto loop
:end
exit
