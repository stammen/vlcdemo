#VLC UWP Demo


The VLC demo project wraps the Win32 [VLC media
player](http://www.videolan.org/vlc/index.html) with a UWP app. The UWP app
presents the user with several ads for other Windows Store apps, a Donate to VLC
button, and a means to dismiss the Ad view and go directly to the VLC player.
Selecting any option in the UWP front end will launch the VLC player and dismiss
the UWP app.

A Windows 10 UWP AppX of this demo is
[available](https://1drv.ms/u/s!ApzPPQxU0_aThvksl736QlJhqGV1iA). Note: This
version is x64 only.

On launch (and eventually first launch only) of the VLC UWP app, the user is
presented with the following UI:

![VLC Demo UWP App](media/3268979d48cf307b594b42bd97c08752.png)

VLC Demo UWP App

Selecting any option on the page will launch the Win32 VLC player and termimate
the VLC UWP app.

![Win32 VLC Player](media/4d954365c2d2ed16692f51dee511cb7c.png)

Win32 VLC Player

The VLC player (currently version 2.2.4) runs as a Win32 FullTrust application
and therefore all of its features should be available to the user. (This needs
to be fully tested)

The work to build this demo explored 2 areas:

1.  Build VLC as a Centennial App with the [Desktop App
    Converter](https://docs.microsoft.com/en-us/windows/uwp/porting/desktop-to-uwp-run-desktop-app-converter)

2.  Build VLC as a UWP app that contains all of the VLC files. Using the Desktop
    App Converter is not required.

The UWP VLC Demo app was built without using the Desktop App Converter. All of
the VLC app files are contained in the UWP app. The Win32 VLC player app is
launched from wihin the UWP app as a FullTrust process.

##How to convert VLC to a Centennial App using the Desktop App Converter

Although the UWP VLC demo did not use the Desktop App Converter to create the
demo app, the process for converting VLC to a Centennial App is documented
below. The AppxManifest.xml create by the Desktop App Converter is useful for
adding the file associations to the UWP version.

1.  Install the [Desktop App
    Converter](https://docs.microsoft.com/en-us/windows/uwp/porting/desktop-to-uwp-run-desktop-app-converter)

2.  Download the VLC player [installer](http://www.videolan.org/vlc/index.html)
    (currently v.2.2.4). There is no need to run the installer.

3.  Run the Desktop App Converter as administrator.

4.  Convert the VLC player to a Centennial App with the Desktop App Converter.
    The command below assumes you are in the directory where you downloaded the
    VLC installer.

```console
DesktopAppConverter.exe -Installer .\vlc-2.2.4-win32.exe -InstallerArguments "/L=1033 /S" -Destination .\output -PackageName "VLC" -Publisher "CN=vlc" -Version 2.2.4.0 -MakeAppx -Verbose -Sign
```

-   The InstallerArguments "/L=1033 /S" specify the english version of VLC
    (/L=1033) and a silent install (/S)

## Install Certificate

After the conversion is complete open the . folder. You will need to install the
certificate created by the Desktop App Converter. 1. Right click on the
auto-generated.cer file and select *Install Certificate*

![Install Certificate](media/9f612f9293d737c6c5356fe2069ff867.png)

Install Certificate

![Install Certificate](media/f75f77bb9b201d9e330675bce4fec5af.png)

Install Certificate

You will add the certificate to Local Machine Trusted Root Certification
Authorities

![Select Local Machine](media/1bb5935e9963eddb1f78b87b810636f0.png)

Select Local Machine

Select **Local Machine**. Click **Next**.

![Select Certificate Store](media/659071cebb4fa806cc09a7167fc5f7cc.png)

Select Certificate Store

Click the **Browse** button and select **Trusted Root Certification
Authorities**. Click **OK**. Click **Next**. Click **Finish**. The certificate
is now installed.

You can now install the AppX of the VLC app. Double click on the VLC.Appx file.

![VLC AppX](media/eed97117952e50d2cdc6a68075fcaf79.png)

VLC AppX

Click on **Install**

![Install VLC](media/0ec517175ca456178a748e90cbc39625.png)

Install VLC

You can now launch the Centennial version of VLC

![Launch VLC](media/6b4d79822b5c929034ef37a61d295514.png)

Launch VLC

## Building the UWP VLC Demo App

The source code to the UWP VLC demo app is currently in a [private github
repo](https://github.com/stammen/vlcdemo). Please email <dalestam@microsoft.com>
with your github username to obtain access to the source code.

1. Clone the vlcdemo github repo.

    ```console
       git clone https://github.com/stammen/vlcdemo.git
    ```
    or with SSH

    ```console
        git clone git@github.com:stammen/vlcdemo.git
    ```

1. cd vlcdemo

1. Install the VLC player files into the project

    ```console
        .\get-vlc.bat
    ```

1. Open vlcdemo.sln. Select x86 or x64 for the platform. Select Debug or
    Release for the configuration. Build the solution.
    
1. In order to run the vlcdemo, select **Start without Debugging** from the **Debug** menu.

##Creating the AppX Package for the Windows Store
In order to create the AppX package for the Windows Store **do not use the Store option in Visual Studio**. You need to manually create the AppX using the MakeAppx.exe tool.

1. Select Deploy from the Build menu. You should have also selected a Release x64 build

1. After the Deploy build has completed, open a Command Prompt window and cd to vlcdemo\x64\Release\vlcdemo

1. Use the following command to build the AppX for the Windows Store:

    ```console
    "C:\Program Files (x86)\Windows Kits\10\bin\x86\MakeAppx.exe" pack /p .\VLC.appx /d .\AppX /l
    ```
    
1. You will need to sign the VLC.appx file with a certificate. Use the following commands to generate the certificate files.

    ```console
    "C:\Program Files (x86)\Windows Kits\10\bin\x86\MakeCert.exe" -r -h 0 -n "CN=vlc" -eku 1.3.6.1.5.5.7.3.3 -pe -sv vlc.pvk vlc.cer
    "C:\Program Files (x86)\Windows Kits\10\bin\x86\pvk2pfx.exe" -pvk vlc.pvk -spc vlc.cer -pfx vlc.pfx
    ```
    **Note: make sure the "CN=vlc" is the same CN used when the app was deployed. If they are different, you will get an error when trying to sign your appx.**

1. You can now sign the vlc.appx package with the  following command:
 
    ```console
    "C:\Program Files (x86)\Windows Kits\10\bin\x86\signtool.exe" sign -f vlc.pfx -fd SHA256 -v .\VLC.appx
    ```
1. You can now install the VLC.appx on your computer. Make sure any previous versions of VLC are uninstalled. For example, the Build and Deploy step installs the VLC appx, so you will need to unistall it before trying to install VLC.appx.

1. Install the vlc.cer certificate. Follow the same procedure as [Install Certificate](#install-certificate)

1. Double-click on the VLC.appx file. Click on the **Install** button.

1. The vlc demo is now installed on your computer.

##Coding Discussion

###Adding the VLC App Files to the Project

The following code was added to support launching VLC from the UWP app.

A resources.props file was added to the project to copy the VLC files to the
AppX package. The resources.props file automates the adding of all of the VLC
files. The resource.props file was added to the vlcdemo project as follows.

Select **Property Manager** from the **View** menu

![Property Manager](media/678187ce800c6b0b83e585220bec7aa1.png)

Property Manager

Right click on vlcdemo and select **Add Existing Property Sheet...**

![Add Existing Property Sheet](media/3feb5797ba868e4106807277f3bd5693.png)

Add Existing Property Sheet

Select the file **resources.props** from the vlcdemo folder.

![Resources.props](media/c6a8831a848e56b193f397cdd19d52df.png)

Resources.props

Now whenever a build of the vlcdemo project occurs, the VLC app files will be
automatically copied to the AppX. This will also automate adding the VLC apps
files when a Store Package is built.

### Adding the Win32 VLC application to the App Manifest

The vlcdemo UWP app needs to be able to launch the Win32 vlc.exe app as a
FullTrust application. In order to do this, the Win32 vlc.exe app needs to be
added to the Package.appxmanifest file.

The xml of the Package.appxmanifest file must be edited with a text editor.

Right click on the Package.appxmanifest file file in the vlcdemo project. Select
**Open With...** from the pop-up menu.

![Manifest Open With...](media/a4fc0c900b46034e8c59464ce563da7d.png)

Manifest Open With...

Select **XML (Text) Editor** from the list. Click **OK**.

![Manifest Open With...](media/58a2f972a8d38d5e1d39fee9d0a38adc.png)

Manifest Open With...

In the XML editor add the following XML schemas to the Package tag

```xml
    xmlns:rescap="http://schemas.microsoft.com/appx/manifest/foundation/windows10/restrictedcapabilities"
    xmlns:desktop="http://schemas.microsoft.com/appx/manifest/desktop/windows10"
    xmlns:uap2="http://schemas.microsoft.com/appx/manifest/uap/windows10/2" 
    xmlns:uap3="http://schemas.microsoft.com/appx/manifest/uap/windows10/3"
```

Add uap2, uap3, rescap and desktop to IgnorableNamespaces

```xml
    IgnorableNamespaces="uap uap2 uap3 mp rescap desktop"
```

We need to add VLC in an Application tag in the Applications section. I added
the following:

```xml
    <Application Id="VLC" Executable="VLC\vlc.exe" EntryPoint="Windows.FullTrustApplication">
      <uap:VisualElements DisplayName="VLC" Square150x150Logo="Assets\AppMedTile.png" Square44x44Logo="Assets\AppList.png" Description="VLC" BackgroundColor="transparent" AppListEntry="none">
        <uap:DefaultTile Wide310x150Logo="Assets\AppWideTile.png" Square310x310Logo="Assets\AppLargeTile.png">
          <uap:ShowNameOnTiles>
            <uap:ShowOn Tile="square150x150Logo" />
            <uap:ShowOn Tile="wide310x150Logo" />
            <uap:ShowOn Tile="square310x310Logo" />
          </uap:ShowNameOnTiles>
        </uap:DefaultTile>
        <uap:SplashScreen Image="Assets\AppSplashScreen.png" BackgroundColor="black" />
      </uap:VisualElements>
    </Application>
```

It is important to note the **AppListEntry="none"** property in the
uap:VisualElements element. This prevents the Win32 VLC app from appearing in
the Windows application list. Only the UWP app will appear in the Windows
applications list. We launch the Win32 VLC app with the UWP app.

Note: Some work will be needed with the above VLC Application tag to add the
media filetypes supported by VLC. For example, if a user double clicks on a .wav
file, VLC should be launched to play the file.

Note: Specifying multiple Application tags in the Applications section of the
Package.appxmanifest is only allowed for Centennial Apps. Pure UWP apps will
fail WACK if more than one application is specified in the Applications section.

Note: The tiles specified in the Package.appxmanifest file were copied from the
Centennial version of VLC generated with the Desktop App Converter.

### Launching VLC from the UWP App ###

Now that we have added the Win32 VLC app files to the project and the vlc.exe as
a application to the Package.appxmanifest file, we can now launch vlc.exe from
the UWP app. In MainPage.xaml.cpp, take a look at the function

```cpp
void vlcdemo::MainPage::StartVLC(Windows::UI::Core::CoreDispatcher^ dispatcher)
{
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
```

This function does 2 things. First it launches the vlc.exe as a FullTrust Win32
app. After the launch is complete, it exits the UWP app so only the Win32 VLC
app is presented to the user. This function uses the relatively undocumented
Windows::ApplicationModel::Package::Current-\>GetAppListEntriesAsync() method to
get the list of Applications specified in the Package.appxmanifest file. Once we
have the list, we get the AppListEntry for the vlc.exe (the 2nd position in the
list) and call LaunchAsync() to launch vlc.exe. We then use the
Windows::UI::Core::CoreDispatcher to terminate the UWP app from the UI thread,
allowing vlc.exe to launch before we terminate the UWP app.

The MainPage.xaml.cpp file contains all of the other functionality of the demo
app including launching the Windows Store, the VLC donation page, etc.
