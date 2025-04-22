// platform.h
// By Gabriel Staples
// Apr. 2025
// 
// From: 
// 1. https://stackoverflow.com/a/79228659/4561887
// 2. https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/src/platform.cpp
// 
// Print out some messages at compile time to show which platform we are 
// compiling on.
// - This helps us debug so we can get the correct static asserts on sizes 
//   for the various platforms on which we compile. 
// - See also: 
//   1. https://sourceforge.net/p/predef/wiki/OperatingSystems/
// 
// Note that on my 64-bit x86-64 computer, the sizes of types are the same on 
// `__CYGWIN__` (using the base MSYS2 terminal) on Windows as they are on
// `__gnu_linux__` on Linux. 

#pragma once

#pragma message(">>> Detecting your platform... <<<")
#ifdef unix
    #pragma message("Compiling on unix")
#endif
#ifdef __unix
    #pragma message("Compiling on __unix")
#endif
#ifdef __unix__
    #pragma message("Compiling on __unix__")
#endif
#ifdef linux
    #pragma message("Compiling on linux")
#endif
#ifdef __linux__
    #pragma message("Compiling on __linux__")
#endif
#ifdef __gnu_linux__
    #pragma message("Compiling on __gnu_linux__")
#endif
#ifdef _WIN32
    #pragma message("Compiling on _WIN32")
#endif
#ifdef _WIN64
    #pragma message("Compiling on _WIN64")
#endif
#ifdef __WIN32__
    #pragma message("Compiling on __WIN32__")
#endif
#ifdef __CYGWIN__
    #pragma message("Compiling on __CYGWIN__")
#endif
#ifdef __MINGW32__
    #pragma message("Compiling on __MINGW32__")
#endif
#ifdef __MINGW64__
    #pragma message("Compiling on __MINGW64__")
#endif
#ifdef __GNUC__
    #pragma message("Compiling on __GNUC__")
#endif
