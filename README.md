# eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2

A demo of an elegant, cross-platform, multi-layered build system project which builds Linux/Unix sockets on both Linux and Windows, using MSYS2 in Windows.


# References

1. My repo: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/tree/master/CMake
1. My answer: [Installing & setting up MSYS2 from scratch, including adding all 7 profiles to Windows Terminal...](https://stackoverflow.com/a/77407282/4561887)
    1. [Part 2 of the above answer](https://stackoverflow.com/a/79203485/4561887) - I talk about sockets and DLLs here. 
1. My answer: [How to package a "portable" MSYS2-built Windows application with all required DLLs to run in any Windows environment or terminal](https://stackoverflow.com/a/79569000/4561887)
1. CMake documentation:
    1. Tutorial: https://cmake.org/cmake/help/latest/guide/tutorial/index.html
    1. All commands: https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html
    1. `CMakePresets.json` and `CMakeUserPresets.json`: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html


# Linux Setup

_Tested in Ubuntu 22.04._

```bash
# Install gcc-13 so we can have access to the `std::format()` library, here: 
# https://en.cppreference.com/w/cpp/utility/format/format
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install gcc-13 g++-13

# Install the latest version of CMake from here: https://cmake.org/download/
mkdir -p ~/Downloads/Install_Files/CMake
cd ~/Downloads/Install_Files/CMake
wget https://github.com/Kitware/CMake/releases/download/v4.0.0/cmake-4.0.0-linux-x86_64.sh
chmod +x cmake-4.0.0-linux-x86_64.sh
# TODO: figure out the param to pass to skip the prompts and auto-accept them all instead. 
./cmake-4.0.0-linux-x86_64.sh  # Install, choose Y twice when needed
# Make symlinks to all 5 cmake executables.
# - Alternatively, you could add `cmake-4.0.0-linux-x86_64/bin` to your PATH instead.
mkdir -p ~/bin
cd cmake-4.0.0-linux-x86_64/bin
ln -si "$(pwd)/ccmake" ~/bin
ln -si "$(pwd)/cmake" ~/bin
ln -si "$(pwd)/cmake-gui" ~/bin
ln -si "$(pwd)/cpack" ~/bin
ln -si "$(pwd)/ctest" ~/bin
# Re-source
. ~/.profile
# Check the cmake version to ensure it worked
cmake --version  # Should be 4.0.0
```


# Windows Setup

_Tested in Windows 11._

1. Install MSYS2, following my answer here: [Installing & setting up MSYS2 from scratch, including adding all 7 profiles to Windows Terminal...](https://stackoverflow.com/a/77407282/4561887)
1. In the **msys2** terminal, since it has cygwin as its C library and supports Unix sockets on Windows, run the following:
    ```bash
    # Update the package database and core system packages; run repeatedly
    # until no more updates are available
    pacman -Suy  

    # Install gcc
    pacman -S gcc

    # Install CMake
    pacman -S cmake

    # Install make
    pacman -S make

    # Install gdb
    pacman -S gdb

    # Install ccache
    pacman -S ccache
    ```
1. Run `make clean` before building again. 
1. Build and run with: 
    ```bash
    # In one terminal, build, and then run the server first
    time make
    ./build/Release/Server
    
    # In another terminal, run the client 2nd
    ./build/Release/Client
    ```


# Build Instructions

```bash
# Clean and build everything
./build.sh

# Or: call the make commands directly, which are otherwise called by build.sh
make clean
make

# More-granular
make debug
make release
make portable


# Lower-level bash script called by make
./cmake_configure_and_build.sh "debug"
./cmake_configure_and_build.sh "release"

# Lower-level CMake preset commands called by cmake_configure_and_build.sh
# - Configure and build Release, for example
cmake --preset Release           # Configure; ie: have CMake generate the Make build system
cmake --build --preset Release   # Build the project

# Lower-level still, CMake configure command triggered by the preset CMake calls above
mkdir -p build/Release
cd build/Release
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../..
# Then build via a CMake call, using the underlying generator build system specified above 
# (Unix Makefiles in this case)
# - Note: `-j $(nproc)` uses all available cores
cmake --build . -j "$(nproc)"
# OR, now build via the lower-level Make command
make -j "$(nproc)"
```


# Run Instructions

```bash
# Run the server (first) then client (2nd)
./build/Release/Server  # in one terminal
./build/Release/Client  # in another terminal

# Debug the simulation with gdb
gdb build/Debug/Server
gdb build/Debug/Client
```


# Build and run all at once

There are many ways. Here are some examples: 
```bash
# Build and run release only
time make release && ./build/Release/Server  # in one terminal
./build/Release/Client                       # in another terminal

# Create the portable directory with packaged DLLs
make portable 
```


# Example run and output

_Tested and works on:_
1. _[x] Linux Ubuntu 22.04_
1. _[x] Windows 11_

1. Build:
    ```bash
    make clean
    make
    ```

1. Run the server in one terminal:
    ```bash
    ./build/Portable/Server
    ```

1. Run the client in another terminal:
    ```bash
    ./build/Portable/Client
    ```

1. Here is the output from the server in terminal 1: 
    ```bash
    eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2$ ./build/Portable/Server 
    STARTING UDP SERVER:
    1. Create a socket object, obtain a file descriptor to it, and prepare server and client `struct sockaddr_in` internet namespace ("in") socket addresses.
    2. Bind the socket object with the server address specified above so that it can be used.
    3. Block until a message is received.
    4. Process the received message, & print out address info. of the sender, followed by the message!
    Sender (client) address information:
      socket internet namespace (sin) address family name = AF_INET (IPv4 address)
      port                                                = 36703
      IP address                                          = 127.0.0.1
    Msg received from sender (client) (19 bytes):
      Hello from client.
    5. Send a response back to the sender of the message we just received.
    Done! This msg was just sent to the client:
      Hello from server.
    ```

1. Here is the output from the client in terminal 2: 
    ```bash
    eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2$ ./build/Portable/Client 
    STARTING UDP CLIENT:
    1. Create a socket object and obtain a file descriptor to it.
    2. Send a message to the server.
    Done! This msg was just sent to the server:
      Hello from client.
    3. Block until a message is received.
    4. Process the received message, & print out address info. of the sender, followed by the message!
    Sender (server) address information:
      socket internet namespace (sin) family name = AF_INET (IPv4 address)
      port                                        = 20000
      IP address                                  = 127.0.0.1
    Msg received from sender (server) (19 bytes):
      Hello from server.
    ```
