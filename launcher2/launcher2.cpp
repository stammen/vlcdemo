// launcher2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "launcher2.h"
#include <conio.h>
#include <Windows.h>
#include <string>
#include <fcntl.h>  
#include <io.h>
#include <ppltasks.h>
#include <Pathcch.h>
#include <Shlobj.h>

using namespace Windows::Foundation;
using namespace Windows::System;

bool LaunchVLCAds()
{
    bool done = false;
    auto testAppUri = ref new Uri("vlc-ads:"); // The protocol handled by the launched app
    auto options = ref new LauncherOptions();
    concurrency::task<bool> task(Launcher::LaunchUriAsync(testAppUri, options));
    return task.get();
}


bool LaunchVLC()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    wchar_t dir[MAX_PATH];

    GetModuleFileName(NULL, dir, MAX_PATH);
    PathCchRemoveFileSpec(dir, wcslen(dir));
    std::wstring path = dir;
    path += L"\\VLC\\vlc.exe";

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process. 
    int retvalue = CreateProcess(path.c_str(),
        NULL,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi            // Pointer to PROCESS_INFORMATION structure
    );

    int lastError = GetLastError();
    return lastError == 0;
}

[Platform::MTAThread]
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,  
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    
    wchar_t buf[MAX_PATH];
    auto hr = SHGetFolderPathW(NULL, CSIDL_APPDATA | CSIDL_FLAG_CREATE, NULL, SHGFP_TYPE_CURRENT, buf);
    std::wstring path = buf;
    path += L"\\vlcdemo-firstrun.txt";

    auto h = CreateFile2(path.c_str(), GENERIC_READ, 0, OPEN_EXISTING, NULL);
    if (h != INVALID_HANDLE_VALUE)
    {
        CloseHandle(h);
        LaunchVLC();
    }
    else
    {
        auto h = CreateFile2(path.c_str(), GENERIC_READ, 0, CREATE_ALWAYS, NULL);
        if (h != INVALID_HANDLE_VALUE)
        {
            CloseHandle(h);
        }
        LaunchVLCAds();
    }

    return 0;
}

