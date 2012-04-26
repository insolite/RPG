echo off
cls
echo Please enter the game name
set /p gamename=
start Server.exe %gamename%
start Client.exe