cmake_minimum_required(VERSION 3.23)
project(Sockets)

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
