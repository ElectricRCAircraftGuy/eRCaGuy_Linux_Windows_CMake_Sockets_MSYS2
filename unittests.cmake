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

# Function to configure a test target
function(configure_test_target target)
    # See: https://cmake.org/cmake/help/latest/command/target_compile_definitions.html
    target_compile_definitions(${target} PRIVATE 
        -DTESTING
    )
    target_link_libraries(${target} 
        GTest::gtest_main 
        compiler_flags
    )
    gtest_discover_tests(${target} 
        EXTRA_ARGS --gtest_color=yes  # always run with colored output
    )
endfunction()

# -----------------------------------------------------------
# --- Add your unit tests here now, one at a time [START] ---
# -----------------------------------------------------------

add_executable(main_client_unittest
    "src/main_client_unittest.cpp"
)
configure_test_target(main_client_unittest)

add_executable(main_server_unittest
    "src/main_server_unittest.cpp"
)
configure_test_target(main_server_unittest)

# -----------------------------------------------------------
# --- Add your unit tests here now, one at a time [END] ---
# -----------------------------------------------------------
