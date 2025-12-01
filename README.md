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

## Build instructions for macOS and Windows

### Setup Dependencies
You need
- A C++ compiler
- CMake
- Qt Libraries

#### macOS

The quickest way is
```bash
xcode-select --install # Installs the xcode tools, including git and a C++ compiler. If you used git to clone this repo, you can skip this line
brew install cmake
brew install qt # Installs a full set of Qt libraries, including all of the ones qt-remit needs
```

#### Windows

Install the [Build Tools for Visual Studio](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022).

Install Qt through the [Qt OSS online installer](https://www.qt.io/download-qt-installer-oss).

At the time of writing, the latest version is 6.9.1. The WebEngine part may have moved since then (it also moved between 6.6 and 6.9)

Do a custom installation and make sure you install
- Extensions -> Qt WebEngine -> Qt 6.9.1
- Qt -> 6.9.1 -> Desktop
- Qt -> Build Tools -> CMake 3.30.5 (the version doesn't matter)


### Building qt-remit

```bash
make
```

This should generate a binary at `build/qt-remit` that you can run, as long as it can find a Qt6 that has the WebEngineWidgets installed.

### Packaging qt-remit

On macOS, the build steps above produce an application package.
Drop that into your `/Applications` folder to have it available from your launcher of choice.

On Windows, the build steps produce a self-contained binary. Drop that wherever you want to execute it from and set up a link.

## Build instructions for Linux

Building and installing on Linux is more straight forward, just copy and paste the line below.

This is for Ubuntu/Linux Mint/etc. If you're on a different distro that doesn't package Qt in a comparable way, check the Windows section above for how to install Qt from the online installer.

```bash
sudo apt install -y build-essential cmake qt6-base-dev qt6-webengine-dev qt6-webchannel-dev && make && sudo make install

# sudo make install PREFIX=/opt/qt-remit # on linux in a custom prefix
```

You can use the icon in `resources/` when setting up a app launcher.

## Is it any good?

Yes.
