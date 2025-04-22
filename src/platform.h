// platform.h
// By Gabriel Staples
// Apr. 2025
// 
// From: 
// 1. https://stackoverflow.com/a/79228659/4561887
// 2. https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/src/platform.h
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

// Automatically defined by your compiler/OS/platform

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
#ifdef __MSYS__
    #pragma message("Compiling on __MSYS__")
#endif
#ifdef __GNUC__
    #pragma message("Compiling on __GNUC__")
#endif

// Custom `MSYSTEM_*` definitions added by me directly via CMakeLists.txt.
// - This is based on the fact that possible `MSYSTEM` environment variable 
//   values set by the MSYS2 terminal environment on Windows include:
//  
//   1. MSYS
//   2. MINGW32
//   3. MINGW64
//   4. UCRT64
//   5. CLANG64
//   6. CLANG32
//   7. CLANGARM64
// 
// - See my answer here: https://stackoverflow.com/a/79201770/4561887

#ifdef MSYSTEM_MSYS
    #pragma message("Compiling on MSYSTEM_MSYS")
#endif
#ifdef MSYSTEM_MINGW32
    #pragma message("Compiling on MSYSTEM_MINGW32")
#endif
#ifdef MSYSTEM_MINGW64
    #pragma message("Compiling on MSYSTEM_MINGW64")
#endif
#ifdef MSYSTEM_UCRT64
    #pragma message("Compiling on MSYSTEM_UCRT64")
#endif
#ifdef MSYSTEM_CLANG64
    #pragma message("Compiling on MSYSTEM_CLANG64")
#endif
#ifdef MSYSTEM_CLANG32
    #pragma message("Compiling on MSYSTEM_CLANG32")
#endif
#ifdef MSYSTEM_CLANGARM64
    #pragma message("Compiling on MSYSTEM_CLANGARM64")
#endif
#ifdef MSYSTEM_NOTSET
    #pragma message("Compiling on MSYSTEM_NOTSET (ie: probably Linux)")
#endif
