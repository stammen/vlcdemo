//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <ppltasks.h>

using namespace vlcdemo;

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
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
	InitializeComponent();
}

void vlcdemo::MainPage::StoreButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto dispatcher = Window::Current->CoreWindow->Dispatcher;
    Windows::ApplicationModel::FullTrustProcessLauncher::LaunchFullTrustProcessForCurrentAppAsync();
    auto uri = ref new Windows::Foundation::Uri(L"https://www.microsoft.com/en-us/store/p/vlc/9nblggh4vvnh");
    concurrency::task<bool> launchUriOperation(Windows::System::Launcher::LaunchUriAsync(uri));
    launchUriOperation.then([dispatcher](bool result)
    {
        dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([=]()
        {
            Windows::UI::Xaml::Application::Current->Exit();
        }));
    });
}

void vlcdemo::MainPage::HyperlinkButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto dispatcher = Window::Current->CoreWindow->Dispatcher;
    auto t = create_task(Windows::ApplicationModel::Package::Current->GetAppListEntriesAsync());
    t.then([dispatcher](IVectorView <Windows::ApplicationModel::Core::AppListEntry^>^ entries)
    {
        auto entry = entries->GetAt(1);
        auto t2 = create_task(entry->LaunchAsync());
        t2.then([dispatcher](bool)
        {
            dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([=]()
            {
                Windows::UI::Xaml::Application::Current->Exit();
            }));
        });
    });
}

void vlcdemo::MainPage::DonateButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto dispatcher = Window::Current->CoreWindow->Dispatcher;
    Windows::ApplicationModel::FullTrustProcessLauncher::LaunchFullTrustProcessForCurrentAppAsync();
    auto uri = ref new Windows::Foundation::Uri(L"http://www.videolan.org/contribute.html");
    concurrency::task<bool> launchUriOperation(Windows::System::Launcher::LaunchUriAsync(uri));
    launchUriOperation.then([dispatcher](bool result)
    {
        dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([=]()
        {
            Windows::UI::Xaml::Application::Current->Exit();
        }));
    });
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

    auto dispatcher = Window::Current->CoreWindow->Dispatcher;
    Windows::ApplicationModel::FullTrustProcessLauncher::LaunchFullTrustProcessForCurrentAppAsync();
    concurrency::task<bool> launchUriOperation(Windows::System::Launcher::LaunchUriAsync(uri));
    launchUriOperation.then([dispatcher](bool result)
    {
        dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([=]()
        {
            Windows::UI::Xaml::Application::Current->Exit();
        }));
    });
}
