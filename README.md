# nyx-core
zEngine extensions for [Project Nyx aka PHOENIX](https://phoenixthegame.com/) by [PhoenixTales](https://phoenixtales.de/).

## ReadMe ToDo
- [ ] compile nyx-core after verifying toolchain: C++ include path `${NYXCORE_ROOT}`?
- [ ] plugin config in mod.ini?
- [ ] current caveats: empty parser error on start
- [ ] documentation of core classes: `oCNPCEx.cpp` (extended attributes), `oCGameEx.cpp` (HUD), `ParserExtender_Externals.h` (new externals)
- [ ] on first start GothicMod.exe after Union install: MSVCR100.dll missing
- [ ] GitHub build automation?


# Installation
Below are the instructions to download and compile the nyx-core in a vanilla Gothic installation.
In the following instructions, we will refer to the root path of the Gothic installation as `GOTHIC_ROOT` and to the local root of this repository as `NYXCORE_ROOT`.


## Prerequisites
- Windows 10, x64 version
- a clean CD or [GOG](https://www.gog.com/game/gothic) installation of Gothic
- (optional) a browser with an auto-translate plugin (e.g. Chrome), if you do not speak Russian since many resources related to the Union SDK are only available in Russian at the [developers' forum](https://worldofplayers.ru/forums/1141/)


## Install Union PlayerKit
- Download and install the [.NET Framework 4.0](https://www.microsoft.com/en-US/download/details.aspx?id=17718)
<!-- - Download and install the [.NET Framework 4.8 Developer Pack](https://dotnet.microsoft.com/download/dotnet-framework/net48) -->
- Download and install the [Windows SDK 7.1](https://www.microsoft.com/en-US/download/details.aspx?id=8279)
- Download and install the [Visual C++ 2010 toolchain](https://www.microsoft.com/en-us/download/details.aspx?id=4422).
<!-- - Download and install the [Visual C++ 2010 toolchain](https://www.microsoft.com/en-us/download/details.aspx?id=26999). -->
- Download and install the [Union Resource Manager](https://worldofplayers.ru/threads/41415/). The installation directory will be referred to as `UNION_ROOT`.
  - Launch the `Union Resource Manager` (`${UNION_ROOT}/GUI.exe`) and click on the tab `Union`.
  - Click `Player Kit + Patch for x64 systems` to download and install the Player Kit which provides the mod launcher.
    - The following new files should be added to `${GOTHIC_ROOT}/system`: `GothicMod.exe`, `GothicStarter.exe`, `GothicStarter_mod.exe`
  - Click on the latest Union version in the list (e.g. `Union 1.0k`) to download and install it.
    - The following new files should be added to `${GOTHIC_ROOT}/system`: `Union.patch`
- Launch `${GOTHIC_ROOT}/system/GothicMod.exe`. The splash screen as well as the main menu should now display your installed Union version.


## Install Gothic MDK and nyx-core demo
- Download the latest release of the [Gothic Development Kit](https://github.com/PhoenixTales/gothic-devkit/releases) and unpack into a new directory (refered to as `DEVKIT_ROOT`).
  - Copy the content of `${DEVKIT_ROOT}/gothic/` into `${GOTHIC_ROOT}/`.
- Copy the content of `${NYXCORE_ROOT}/demo/` into `${GOTHIC_ROOT}/`. Overwrite all file conflicts at the destination.


## Set up Visual Studio toolchain
- Download and install the [Visual Studio Community IDE](https://visualstudio.microsoft.com/vs/community/), 2019 or later.
  - Install the defaults of the Visual C++ development environment.
- Go back into `Union Resource Manager` and switch to the tab `Union SDK`.
  - Click on the latest SDK which is compatible with the installed Union version. E.g., if `Union 1.0k` was installed earlier, please select version `1.0k` for the SDK, too.
  - If successfully installed, the SDK should be found at `${UNION_ROOT}/sdk/UnionPlugin_1_0k.zip`.
- Verify that the toolchain has been installed correctly by launching `Visual Studio`.
  - Select `File -> New -> Project` and select `UnionPlugin_1_0k`.
  - Set a project name, e.g. `UnionTestPlugin`.
  - After the project has been created, select `Project -> Properties` and change the following settings:
    - In `Configuration Properties -> General -> General`:
      - Set `Platform Toolset` to `Visual Studio 2010 (v100)` to use the correct C++ compiler.
      - Set `Output Directory` to your respective path of `${GOTHIC_ROOT}/system` to ensure that the compiled plugin is saved into the game directory.
    - In `Configuration Properties -> Debugging`:
      - Set `Command` to `$(TargetDir)/GothicMod.exe`. This allows to launch the Gothic in debugging mode straight out of Visual Studio and provides the handling of breakpoints, heap profiles, stack traces etc.
      - Set `Command Arguments` to `-game:nyx_playground.ini -zwindow -devmode -vdfs:physicalfirst -zreparse`. This ensures that the demo level config of the nyx-core is loaded.
  - In the top menu, select the build configuration from the drop down list as `G1 Debug`.
  - Launch the debugging mode (F5). The solution should compile without errors and launch into a vanilla main menu. After starting a new game, the player should see the demo level.


## Compile nyx-core
- Open `${NYXCORE_ROOT}/NyxCore/NyxCore.sln` in Visual Studio.
- Adjust the project properties in the same way as it was done for the Union test plugin compiled earlier.
- Launch the debugging mode again to compile the `NyxCore.dll`. The game should now launch with the new functionality provided by the plugin.


# Documentation
TODO


## Current Features
- TODO


## Current Caveats
- TODO


## Current Roadmap
- TODO


# Additional Resources

## Download Links
- [.NET Framework 4.0](https://www.microsoft.com/en-US/download/details.aspx?id=17718)
- [Windows SDK 7.1](https://www.microsoft.com/en-US/download/details.aspx?id=8279)
- [Visual C++ 2010 toolchain](https://www.microsoft.com/en-us/download/details.aspx?id=4422)
- [Visual Studio Community IDE](https://visualstudio.microsoft.com/vs/community/)
- [Union Resource Manager](https://worldofplayers.ru/threads/41415/)
- [Gothic Devkit](https://github.com/PhoenixTales/gothic-devkit/releases)
- [Ikarus](https://github.com/Lehona/Ikarus/releases)
- [LeGo](https://github.com/Lehona/LeGo/releases)
- [Ninja](https://github.com/szapp/Ninja/releases)


## Union Documentation
- [SDK Manual](https://worldofplayers.ru/threads/42146/)
- [SDK Forum](https://worldofplayers.ru/forums/1143/)
- [Resource Manager](https://worldofplayers.ru/threads/41415/)
- [Plugin Forum](https://worldofplayers.ru/forums/1142/)

