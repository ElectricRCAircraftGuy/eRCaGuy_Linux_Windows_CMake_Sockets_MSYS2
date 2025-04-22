cmake_minimum_required(VERSION 3.23)
project(Sockets)

# enable CMake's `ctest` unit testing, which also support gtest
enable_testing()

# Get MSYSTEM environment variable and define it for C and C++ code. 
# - Example `MSYSTEM` values in MSYS2 on Windows are as follows. 
#   See my answer here: https://stackoverflow.com/a/79201770/4561887
#   1. MSYS
#   2. MINGW32
#   3. MINGW64
#   4. UCRT64
#   5. CLANG64
#   6. CLANG32
#   7. CLANGARM64
# - See what `MSYSTEM` is set to by searching 
#   "build/Release/compile_commands.json", for instance, for `-DMSYSTEM` 
#   after building.
set(MSYSTEM_VALUE $ENV{MSYSTEM})
if(MSYSTEM_VALUE)
    add_compile_definitions("MSYSTEM_${MSYSTEM_VALUE}")
else()
    add_compile_definitions("MSYSTEM_NOTSET")
endif()

# Generate a compile_commands.json file for use with clangd. 
# - See: https://cmake.org/cmake/help/latest/variable/CMAKE_EXPORT_COMPILE_COMMANDS.html
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)
target_compile_options(compiler_flags INTERFACE -Wall -Wextra -Werror -O3)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "  Debug build")
    add_compile_options(-ggdb -O0)
endif()

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# Add all include directories
include_directories(
    "src"
)

add_executable(Client
    "src/main_client.cpp"
)

add_executable(Server
    "src/main_server.cpp"
)

target_link_libraries(Client PUBLIC compiler_flags)
target_link_libraries(Server PUBLIC compiler_flags)


# ======= Unit Tests =======
# - See: https://google.github.io/googletest/quickstart-cmake.html
# - NB: `enable_testing()` was already called above.

# For Windows: Prevent overriding the parent project's compiler/linker settings
# See: https://google.github.io/googletest/quickstart-cmake.html
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add the googletest subdirectory
add_subdirectory(src/third_party/googletest)

# Include `GoogleTest` in order to get access to the `gtest_discover_tests()`
# command, which will help `ctest` discover the gtests so it will run them when
# we run `ctest`.
# - See: https://cmake.org/cmake/help/latest/module/GoogleTest.html
include(GoogleTest)

# --- Add your unit tests here now, one at a time [START] ---

add_executable(main_client_unittest
    "src/main_client_unittest.cpp"
)
target_link_libraries(main_client_unittest
    GTest::gtest_main
    compiler_flags
)
gtest_discover_tests(main_client_unittest
    EXTRA_ARGS --gtest_color=yes  # always run with colored output
)

add_executable(main_server_unittest
    "src/main_server_unittest.cpp"
)
target_link_libraries(main_server_unittest
    GTest::gtest_main
    compiler_flags
)
gtest_discover_tests(main_server_unittest
    EXTRA_ARGS --gtest_color=yes  # always run with colored output
)

# --- Add your unit tests here now, one at a time [END] ---
