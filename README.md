# Sapphire - FINAL FANTASY XIV Server Emulator
[![Discord Server](https://img.shields.io/badge/discord-Sapphire-7289DA.svg)](https://discord.gg/KfrZCkx)
[![Build Status](https://travis-ci.org/SapphireMordred/Sapphire.svg?branch=master)](https://travis-ci.org/SapphireMordred/Sapphire)
![FFXIV Sapphire](http://i.imgur.com/I4bj1tR.png)

Sapphire is a FINAL FANTASY XIV 4.0+ Server Emulator currently in development.

## Features

* Fully working base world servers, including character creation, chat, player interaction, etc.
* Basic action/battle system
* Teleports, discovery
* NPCs, enemies
* Support for most Quest types(instanced content planned, to be added later)
* Content scripting via ChaiScript
* Retail GM commands working

## Dependencies + Compiling
Sapphire requires the following software:

| *Name* | *Windows* | *Linux* |
| ------ | --------- | ------- |
| CMake 2.6+ and C++14 capable compiler | [Visual Studio 2017](https://www.visualstudio.com/) | Your favorite C++14 capable compiler |
| Boost 1.63.0 | [Win32 precompiled binaries](https://sourceforge.net/projects/boost/files/boost-binaries/1.63.0/boost_1_63_0-msvc-14.0-32.exe/download) | Boost libraries from your distribution's package manager |
| MySQL Server 5.7 | [Official Site](https://dev.mysql.com/downloads/mysql/) | MySQL server from your distribution's package manager |
| C# Compiler(used for various tools) | [Visual Studio 2017](https://www.visualstudio.com/) \| [Mono](http://www.mono-project.com/) | [Mono](http://www.mono-project.com/) from your distribution's package manager |

**Windows**
Set the environment variables ``BOOST_ROOT_DIR`` and ``BOOST_LIB_DIR`` to ``[boost main folder]`` and ``[boost main folder]/lib32-msvc-14.0`` respectively **or** copy your boost installation into the project's ``src/lib`` folder.
* In *Visual Studio 2017*: Open the project via ``File`` > ``Open`` > ``Folder`` and wait, till CMake automatically finishes cache generation. Right click any CMakeLists.txt and select build to build a application. 
To configure debug startup parameters, select ``Debug and Launch settings``, the application you want to set up parameters for, and add a ``args`` json array containing your launch parameters in ``configurations``.
If Visual Studio fails to generate a CMake Cache or does not show options to build, make sure that the newest version of it is installed and all environment variables are set correctly. Keep in mind that generating a cache can take a while on some machines.
* In *Visual Studio 2015*: Generate a Visual Studio project via CMake: ``cmake -G "Visual Studio 14 2015"`` and open it as a normal solution in Visual Studio.

**Linux**
Generate a cache with CMake and use your favorite C++14 capable compiler to compile those wonderful lines of code into binaries with ``make``.
Sapphire is **not** currently configured to compile in 64bit. Make sure that all libraries have their ``:i386`` versions installed.

## Links

* [Sapphire on YouTube](https://www.youtube.com/channel/UCJKYuovoGsq7PxSAfrNJKbw)

Final Fantasy XIV © 2010-2017 SQUARE ENIX CO., LTD. All Rights Reserved. We are not affiliated with SQUARE ENIX CO., LTD. in any way.
