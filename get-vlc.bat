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
       
echo Downloading vlc 2.2.4...    
call powershell Invoke-WebRequest -OutFile vlc-2.2.4-win64.exe %VLC_URL%
echo Download complete.

echo Installing VLC...
call vlc-2.2.4-win64.exe /L=1033 /S
echo Install complete.

echo Copying VLC files to project...
xcopy /iycqs "%programfiles%\VideoLAN\VLC" .\vlcdemo\VLC
echo Deleting uninstall.exe from .\vlcdemo\VLC
rm .\vlcdemo\VLC\uninstall.exe
echo Copy complete.

echo Note: VLC has been installed on your computer. Please unistall the VLC app if you do not want it.
pause