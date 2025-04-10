#!/usr/bin/env bash

# See: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"

cd "$SCRIPT_DIRECTORY"

echo "Cleaning..."
make clean
echo "Building..."
time make || exit 1

echo ""
echo "All output is in the build/ dir."

echo ""
echo "Run with, for example:"
echo "time build/Release/Client"
echo "time build/Release/Server"
echo ""
echo "Debug with the following command, for example:"
echo "gdb build/Debug/Client"
echo "gdb build/Debug/Server"
echo ""
echo "Debug with the following command, for example:"
echo "Press Ctrl + X, A to enter TUI mode."
echo "(Optional) Ctrl + X, o to switch back to the command window."
echo "b main.cpp:14 to set a breakpoint at line 14 of main.cpp."
echo "r to run to that point."
echo "c to continue."
echo "q to quit."
