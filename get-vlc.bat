@echo off
setlocal

set VLC_URL=http://mirror.os6.org/videolan/vlc/2.2.4/win64/vlc-2.2.4-win64.exe
set STARTDIR=%cd%
set LOGFILE=%~dp0\build.log

if exist .\vlcdemo\VLC (
	rm -rf .\vlcdemo\VLC
)

if exist vlc-2.2.4-win64.exe (
    rm vlc-2.2.4-win64.exe
)
        
call curl -O -L %VLC_URL%

call vlc-2.2.4-win64.exe "/L=1033 /S"

xcopy /iycqs "%programfiles%\VideoLAN\VLC" .\vlcdemo\VLC
rm .\vlcdemo\VLC\uninstall.exe
pause