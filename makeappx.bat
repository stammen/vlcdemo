@echo off

if "%1"=="" (
 goto:usage
)

set PUBLISHER=%1

if exist store  (
    rm -rf store
)

mkdir store
pushd store
    if exist vlc.appx  (
        rm vlc.appx 
    )

    "C:\Program Files (x86)\Windows Kits\10\bin\x86\MakeAppx.exe" pack /p .\vlc.appx /d ..\x64\Release\vlcdemo\AppX /l
    "C:\Program Files (x86)\Windows Kits\10\bin\x86\MakeCert.exe" -r -h 0 -n "CN=%PUBLISHER%" -eku 1.3.6.1.5.5.7.3.3 -pe -sv cert.pvk cert.cer
    "C:\Program Files (x86)\Windows Kits\10\bin\x86\pvk2pfx.exe" -pvk cert.pvk -spc cert.cer -pfx cert.pfx
    "C:\Program Files (x86)\Windows Kits\10\bin\x86\signtool.exe" sign -f cert.pfx -fd SHA256 -v .\vlc.appx
popd

goto:eof

:usage
echo please specify your publisher name!
echo usage: makeappx.bat publishername

