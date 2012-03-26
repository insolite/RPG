goto start
-----------------------------
This script separates game,
created in the Editor,
in two parts: Client-side and Server-side
Warning! The script does not separate db.sqlite yet
-----------------------------
:start
echo off
cls
echo Enter the game name
set /p gamename=
mkdir server\%gamename%
xcopy game\%gamename%\db.sqlite server\%gamename%
mkdir client\%gamename%
xcopy /e game\%gamename% client\%gamename%
echo.
echo Done!
echo.
pause
