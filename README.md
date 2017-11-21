# Sapphire - FINAL FANTASY XIV Server Emulator
[![Discord Server](https://img.shields.io/badge/discord-Sapphire-7289DA.svg)](https://discord.gg/xxcdCER)
[![Linux Build Status](https://travis-ci.org/SapphireMordred/Sapphire.svg?branch=master)](https://travis-ci.org/SapphireMordred/Sapphire)
[![Windows Build Status](https://ci.appveyor.com/api/projects/status/lil7lxa3ty165emm?svg=true)](https://ci.appveyor.com/project/SapphireMordred/Sapphire)
![FFXIV Sapphire](http://i.imgur.com/I4bj1tR.png)

Sapphire is a FINAL FANTASY XIV 4.0+ Server Emulator currently in development.

Sapphire is a **research project** to learn how retail servers work and currently not production code; at this time it is **insecure** (use throwaway passwords for accounts) and you should expect a lot of things unimplemented or broken (of course contributions are always welcome).

## Dependencies + Compiling
Sapphire requires the following software:

| *Name* | *Windows* | *Linux* |
| ------ | --------- | ------- |
| CMake 2.6+ and C++14 capable compiler | [Visual Studio 2017](https://www.visualstudio.com/) | `gcc 4.9` and `g++ 4.9` or newer |
| Boost 1.63.0 | [Win32 precompiled binaries](https://sourceforge.net/projects/boost/files/boost-binaries/1.63.0/boost_1_63_0-msvc-14.0-32.exe/download) | Boost libraries from your distribution's package manager |
| MySQL Server 5.7 | [Official Site](https://dev.mysql.com/downloads/mysql/) | MySQL server from your distribution's package manager |

**Windows**
Set the environment variables ``BOOST_ROOT_DIR`` and ``BOOST_LIB_DIR`` to ``[boost main folder]`` and ``[boost main folder]/lib32-msvc-14.0`` respectively **or** copy your boost installation into the project's ``src/lib`` folder.

Visual Studio 2017 users: open `Visual Studio Installer` and ensure `Individual Components > SDKs, libraries, and frameworks > Windows Universal C Runtime` is installed. You may also need to install `Individual Components > Compilers, build tools, and runtimes > VC++ 2015.3 v140 toolset for desktop (x86, 64)`.

To enable [Edit and Continue](https://msdn.microsoft.com/en-us/library/esaeyddf.aspx) ensure you define `-DCMAKE_BUILD_TYPE="Debug"` when generating with CMake.

If you installed CMake outside of Visual Studio and have it in your `PATH` environment variable, navigate to Sapphire folder and `cmake -DCMAKE_BUILD_TYPE="Debug" && cmake --build .`.

Otherwise:
* In *Visual Studio 2017*: Open the project via ``File`` > ``Open`` > ``Folder`` and wait, till CMake automatically finishes cache generation. Right click any CMakeLists.txt and select build to build a application. 
To configure debug startup parameters, select ``Debug and Launch settings``, the application you want to set up parameters for, and add a ``args`` json array containing your launch parameters in ``configurations``.
If Visual Studio fails to generate a CMake Cache or does not show options to build, make sure that the newest version of it is installed and all environment variables are set correctly. Keep in mind that generating a cache can take a while on some machines.

The solution `Sapphire.sln` is also generated in the main Sapphire folder.

**Linux**
`cmake . -DSAPPHIRE_BOOST_VER="your.boost.ver" && make -j JOBS` where `JOBS` is number of cores on your system.  
`-j JOBS` can be omitted if your system lacks resources (spoiler: your system probably lacks resources if running on 1GB RAM or lower, or if the build fails due to being out of memory)

## Links

* [Sapphire on YouTube](https://www.youtube.com/channel/UCJKYuovoGsq7PxSAfrNJKbw)

Final Fantasy XIV © 2010-2017 SQUARE ENIX CO., LTD. All Rights Reserved. We are not affiliated with SQUARE ENIX CO., LTD. in any way.
