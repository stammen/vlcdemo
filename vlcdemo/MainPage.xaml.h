//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace vlcdemo
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

  private:
      void DonateButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
      void InstallAdButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
      void HyperlinkButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
      void StartVLC(Windows::UI::Core::CoreDispatcher^ dispatcher);
      void vlcdemo::MainPage::LoadUrl(Windows::Foundation::Uri^ uri);
    };
}
