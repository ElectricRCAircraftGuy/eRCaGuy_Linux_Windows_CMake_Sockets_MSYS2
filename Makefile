# This is a simple wrapper Makefile which calls other Bash scripts which call CMake, 
# which generates Makefiles and builds with make. 

# Mark all targets as PHONY (not real files)
.PHONY: all clean debug release portable test
all: \
	debug \
	release \
	portable \
	test

clean:
	rm -rf build/

# Build debug
debug:
	./cmake_configure_and_build.sh "debug"

# Build release
release:
	./cmake_configure_and_build.sh "release"

# Build a portable distribution of the executables and DLLs in a single dir
portable: release
	./make_portable.sh "Client"
	./make_portable.sh "Server"

# Run the unit tests
test: release
	ctest --test-dir build/Release/ --output-on-failure
