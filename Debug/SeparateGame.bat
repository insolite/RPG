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
xcopy /y /e editor\%gamename%\db.sqlite server\%gamename%
mkdir server\%gamename%\script
xcopy /y /e editor\%gamename%\script server\%gamename%\script
mkdir client\%gamename%
xcopy /y /e editor\%gamename%\db.sqlite client\%gamename%
mkdir client\%gamename%\model
xcopy /y /e editor\%gamename%\model client\%gamename%\model
echo.
echo Done!
echo.
pause
