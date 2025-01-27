# Remit client in Qt

## What does it do?

Show you remit and github side-by-side, so you can review comfortably.

## Why a third client?

Because the other two only work on macOS and one bold developer had to use Linux.

## Setting things up

> [!NOTE]
> This flow isn't ideal. There's an [issue](https://github.com/barsoom/qt-remit/issues/4) to build a Dialog that prompts for Remit's URL and Token.

1. Run qt-remit. The left pane will show an example page. That's fine, we'll fix that later.
1. Log into Github in the right pane
1. Close qt-remit
1. Find the config file and set the Remit URL and token. qt-remit uses [QStandardPaths::AppConfigLocation](https://doc.qt.io/qt-6/qstandardpaths.html#StandardLocation-enum)
    - on macOS, the file is at `~/Library/Preferences/qt-remit/config.ini`
    - on Linux, the file is at `~/.config/qt-remit/config.ini`
1. Open qt-remit again
1. Go to the remit settings and click "Sign in with Github"

## Build instructions

### Setup Dependencies

You'll need C++ development dependencies. Most linux distros have a package/pattern/package group for that:

- Ubuntu: `sudo apt install build-essential`
- Arch: `sudo pacman -S base-devel`
- OpenSUSE Tumbleweed: `sudo zypper in -t pattern devel_C_C++`
- macOS: `xcode-select --install`. If you have git on your mac, this is done.

You'll also need Qt-development dependencies for Qt6.6. Make sure you install:

- Core
- QWidgets
- QWebEngineCore
- QWebEngineWidgets
- qmake

I installed Qt 6.6.1 through the [Qt OSS online installer](https://www.qt.io/download-qt-installer-oss). If you use that, remember to check "Qt WebEngine" in the "Additional Libraries" for the Qt version you're installing. Just selecting 'Qt for Desktop development' is not enough.

On Linux with Qt 6.6.3 this worked: Custom Installation -> Qt -> 6.6.3 -> gcc, Qt 3D (maybe not needed), Qt WebEngine. Keep CMake and Ninja (needed?) in Build Tools. `sudo apt install libglx-dev libgl1-mesa-dev`. Then follow "Building qt-remit" below.

On macOS: `brew install qt`

Qt SDK Installation through linux package managers is untested (read: Please try setting this up using brew if you have the time!)

### Building qt-remit

1. Clone the repository
1. Create a folder for the build output.
1. `cmake -S path/to/qt-remit/ -O path/to/build/folder`
1. `cd` into the build output folder
1. `make`

This should generate a binary you can put somewhere on your path and run, as long as it can find a Qt6 that has the WebEngineWidgets installed.

### Packaging qt-remit

On OpenSUSE Tumbleweed, `sudo zypper in libQt6WebEngineWidgets6` gets you everything you need, since it depends on everything else qt-remit depends on.
When building a package, make sure this is listed as a requirement.

On macOS, the build steps above produce an application package without an icon. Dropping that into your `/Applications` folder should just work.

## Is it any good?

Yes.
