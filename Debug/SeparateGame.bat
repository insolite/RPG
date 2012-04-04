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
mkdir server\%gamename%\script
xcopy /e game\%gamename%\script server\%gamename%\script
mkdir client\%gamename%
xcopy game\%gamename%\db.sqlite client\%gamename%
mkdir client\%gamename%\texture
xcopy /e game\%gamename%\texture client\%gamename%\texture
echo.
echo Done!
echo.
pause
