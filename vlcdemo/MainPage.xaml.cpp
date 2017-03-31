//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <ppltasks.h>
#include <io.h>
#include <string>
#include <fcntl.h>  

using namespace vlcdemo;

using namespace concurrency;
using namespace Platform;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
    auto folder = Windows::Storage::ApplicationData::Current->LocalFolder;
    std::wstring path = folder->Path->Data();
    path += L"\\vlcdemo-firstrun.txt";

    int fh;
    auto e = _wsopen_s(&fh, path.c_str(), _O_RDONLY, _SH_DENYNO, _S_IREAD | _S_IWRITE);
    if (fh == -1)
    {
        InitializeComponent();
        folder->CreateFileAsync("vlcdemo-firstrun.txt", CreationCollisionOption::ReplaceExisting);
    }
    else
    {
        _close(fh);
        StartVLC(Window::Current->CoreWindow->Dispatcher);
    }
}


void vlcdemo::MainPage::HyperlinkButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto dispatcher = Window::Current->CoreWindow->Dispatcher;
    StartVLC(dispatcher);
}

void vlcdemo::MainPage::DonateButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto uri = ref new Windows::Foundation::Uri(L"http://www.videolan.org/contribute.html");
    HyperlinkButton->Content = L"Launch VLC";
    LoadUrl(uri);
}

void vlcdemo::MainPage::InstallAdButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto button = dynamic_cast<Button^>(sender);
    auto name = button->Name;

    Windows::Foundation::Uri^ uri;
    
    if (name == L"HuluAd")
    {
        uri = ref new Windows::Foundation::Uri(L"ms-windows-store://pdp/?productid=9WZDNCRFJ3L1&referrer=vlcdemo");
    }
    else if (name == L"CandyCrushAd")
    {
        uri = ref new Windows::Foundation::Uri(L"ms-windows-store://pdp/?productid=9NBLGGH18846&referrer=vlcdemo");
    }
    else if (name == L"FitBitAd")
    {
        uri = ref new Windows::Foundation::Uri(L"ms-windows-store://pdp/?productid=9WZDNCRFJ1XX&referrer=vlcdemo");
    }

    HyperlinkButton->Content = L"Launch VLC";
    LoadUrl(uri);
}

void vlcdemo::MainPage::StartVLC(Windows::UI::Core::CoreDispatcher^ dispatcher)
{
    auto t = create_task(Windows::ApplicationModel::Package::Current->GetAppListEntriesAsync());
    t.then([dispatcher](IVectorView <Windows::ApplicationModel::Core::AppListEntry^>^ entries)
    {
        AppListEntry^ vlcEntry = nullptr;

        for (AppListEntry^ entry : entries)
        {
            auto info = entry->DisplayInfo;
            if (info->DisplayName == L"vlc.exe")
            {
                vlcEntry = entry;
                break;
            }
        }

        if (vlcEntry)
        {
            auto t2 = create_task(vlcEntry->LaunchAsync());
            t2.then([dispatcher](bool)
            {
                dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([=]()
                {
                    Windows::UI::Xaml::Application::Current->Exit();
                }));
            });
        }
    });
}

void vlcdemo::MainPage::LoadUrl(Windows::Foundation::Uri^ uri)
{
    concurrency::task<bool> launchUriOperation(Windows::System::Launcher::LaunchUriAsync(uri));
    launchUriOperation.then([this](bool result)
    {
        // update analytics here
    });
}

