# CI status of master branch

[![Ubuntu](https://github.com/johan-boule/warzone2100/actions/workflows/ubuntu.yaml/badge.svg)](https://github.com/johan-boule/warzone2100/actions/workflows/ubuntu.yaml)
[![Windows](https://github.com/johan-boule/warzone2100/actions/workflows/windows.yaml/badge.svg)](https://github.com/johan-boule/warzone2100/actions/workflows/windows.yaml)
[![macOS](https://github.com/johan-boule/warzone2100/actions/workflows/macos.yaml/badge.svg)](https://github.com/johan-boule/warzone2100/actions/workflows/macos.yaml)

<h1 align="center">
  <img src="icons/warzone2100logo.png" alt="Warzone 2100">
  <br />
  Warzone 2100
</h1>

<p align="center">Warzone 2100 is a <b>free, open source, 3D real-time strategy game</b> with a story-driven single-player campaign, online multi-player, offline skirmish, and more.</p>

# Highlights

- Remastered single-player campaign with expanding persistent bases, away missions, and more
- Online multiplayer with up to 10 players, free-for-all or team-play, for massive battles
- Local skirmish with AI bots, for endless replayability
- Extensive tech tree with over 400 different technologies
- Customizable units with a flexible design system that enables a wide variety of possible tactics
- Cross-platform multiplayer
- Support for multiple graphics backends (OpenGL, OpenGL ES, Vulkan)
- 100% free and open source

# Origins

Warzone 2100 was originally developed by Pumpkin Studios and published by Eidos Interactive in 1999.

After fans petitionned for it, in December 2004, the source code was released under an open-source license, followed in June 2008 by movies and sound tracks.
To this day, many volunteer individuals have been maintaining and greatly improving the game.

# State of the game

All original proprietary technologies have been replaced with open-source counterparts, and
extensive improvements and additions have been made throughout while preserving
what made the original release so great.

Development continues, and bug reports & contributions are welcome!

# In-game videos sequences

You can download the videos from [here](https://github.com/Warzone2100/wz-sequences/releases), or [here](https://sourceforge.net/projects/warzone2100/files/warzone2100/Videos/).
You will need to rename the downloaded file to `sequences.wz`, and place it into your Warzone 2100 directory.
Note that `.wz` files are just `.zip` in disguise, you can rename it and extract the content if wish to inspect them.

# Configuration

Warzone 2100 uses its own subdirectory in a user's home directory to save
configuration data, save files and certain other things. Additionally you can
use this directory to place custom maps and mods so the game can find them. The
location of this directory depends on the operating system.

> [!TIP]
> The easy way to find the configuration directory is to:
> 1. Launch Warzone 2100
> 2. Click "Options"
> 3. Click the small "Open Configuration Directory" link in the bottom-left

## Configuration file

The configuration file is just called 'config' and contains several configuration
options, some of them can be changed by using command-line options or using
the in-game menus, others can only be changed by editing the file manually.

If at any point you did something wrong, you can delete the old configuration
file and just restart Warzone 2100. Then the game will regenerate a new
configuration file with default values.

# Command-line options

Warzone 2100 can be started with different options and arguments. For a list
of these options, run the game with the --help option.

Notes: These options all have two dashes (--), not one dash only (-). Also,
if the option has an argument, you need to separate the option and its argument
with a '=' sign - spaces do not work.

Note: Some options have corresponding entries in the configuration file and will
persist from one start of Warzone 2100 to the next.

# Multiplaying via internet

There are two methods to start a multiplayer game via the internet: using the host's
IP or using the lobby server. Make sure you are able to communicate on TCP ports
2100 and 9999. Note that for port forwarding, you only need to configure your
router to forward port 2100.

You can choose whether to connect via Lobby or IP:

* If you choose IP, Warzone 2100 asks you for the IP address of the host and
  will try to connect to that IP.
* If you choose Lobby, Warzone 2100 will connect to the lobby server, as long as
  the lobby-server-address in your config file has not been changed.

You will see a list of games from which you can select.

You can kick unwanted players out of a game before it begins by clicking left on
them while holding the right mouse button.

When you are hosting a game it will automatically be listed on the lobby server.
If you do not want your games to be listed on the lobby-server, you should
change the entry "masterserver_name=warzone2100.retropaganda.info" in your config to some-
thing invalid, for example: "nomasterserverplease".

If you then want to see the games that are listed on the lobby server you have to change
the entry in the config file back. You will have to restart Warzone 2100 in order
for config changes to take effect.

# Cheats

Warzone 2100 has many built-in cheat codes:
* [Warzone 2100 Cheats](doc/Cheats.md)

# Modding information

Warzone 2100 AI, maps and campaign can be scripted using JavaScript.

Links to further information
* [Scripting](doc/Scripting.md)
* [Model format](doc/PIE.md)
* [Animation](doc/Animation.md)

# How to build

## Getting the source

- Clone the Git repo:
  ```shell
  git clone https://github.com/johan-boule/warzone2100.git
  git -C warzone2100 submodule update --init --recursive
  ```
  > Note: Initializing submodules is required.

## Linux

* Prerequisites
   * Compiling tools (ex. CMake, GCC/G++/Clang, ninja-build)
   * Archiving tools (ex. zip, p7zip)
   * Various libraries:
      * [SDL](https://www.libsdl.org) ≥ 3.2.12 _(strongly recommended: ≥ 3.2.26)_
      * [PhysicsFS](https://icculus.org/physfs/) ≥ 2.1 _(strongly recommended: ≥ 3.0.2)_
      * [libpng](https://www.libpng.org/pub/png/libpng.html) ≥ 1.2
      * [libjpeg-turbo](https://github.com/libjpeg-turbo/libjpeg-turbo) ≥ 2.1
      * [libtheora](https://theora.org)
      * [libvorbis](https://xiph.org/vorbis)
      * [libogg](https://xiph.org/ogg/)
      * [opus](https://github.com/xiph/opus)
      * [Freetype](https://www.freetype.org/) _(strongly recommended: ≥ 2.10.4)_
      * [Harfbuzz](https://github.com/harfbuzz/harfbuzz) ≥ 1.0 _(strongly recommended: ≥ 3.3.0)_
      * [fribidi](https://github.com/fribidi/fribidi)
      * [OpenAL-Soft](https://openal-soft.org)
      * [libcurl](https://curl.haxx.se/libcurl/) _(strongly recommended: ≥ 7.58.0)_
      * [libsodium](https://github.com/jedisct1/libsodium) ≥ 1.0.16
      * [SQLite](https://www.sqlite.org/index.html) ≥ 3.14
      * [libzip](https://github.com/nih-at/libzip) _(strongly recommended: ≥ 1.10.1)_
      * [libprotobuf](https://github.com/protocolbuffers/protobuf) (if compiling with GNS support)
   * For language support: [Gettext](https://www.gnu.org/software/gettext/)
   * To generate documentation: [Asciidoctor](https://asciidoctor.org) ≥ 1.5.3
   * To build with Vulkan support: the full [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) _(strongly recommended: ≥ 1.2.148.1)_
* **Installing prerequisites:**
   * Using `get-dependencies_linux.sh`:
      Specify one of the linux distros supported by the script: (`ubuntu`, `fedora`, `alpine`, `archlinux`, `opensuse-tumbleweed`, `gentoo`, `debian`, `raspberrypios`)
      Example:
      ```shell
      sudo ./get-dependencies_linux.sh ubuntu
      ```
* **Building from the command-line:**
   1. Configure how to build:
      ```shell
      cmake -S warzone2100 -B warzone2100.build --install-prefix $PWD/warzone2100.install -G Ninja -D CMAKE_BUILD_TYPE=Release
      ```
      > - The argument  `-S warzone2100` should point to the source directory.
      > - The argument  `-B warzone2100.build` indicates where to create the build directory.
      > - Choose the installation directory by changing the `--install-prefix` argument as desired.
   2. Build:
      ```shell
      cmake --build warzone2100.build --config Release --parallel $(nproc)
      ```
   3. Install:
      ```shell
      cmake --install warzone2100.build --config Release --parallel $(nproc)
      ```
## Windows
See [platforms/windows/README.md](platforms/windows/README.md)

## macOS
See [platforms/macos/README.md](platforms/macos/README.md)

# Licensing

Warzone 2100 is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

[![SPDX-License-Identifier: GPL-2.0-or-later](https://img.shields.io/static/v1?label=SPDX-License-Identifier&message=GPL-2.0-or-later&color=blue&logo=open-source-initiative&logoColor=white&logoWidth=10&style=flat-square)](COPYING)

More information: [COPYING.README](COPYING.README), [COPYING.NONGPL](COPYING.NONGPL)
