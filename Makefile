# This is a simple wrapper Makefile which calls other Bash scripts which call CMake, 
# which generates Makefiles and builds with make. 

# Mark all targets as PHONY (not real files)
.PHONY: all clean debug release portable
all: \
	debug \
	release \
	portable

clean:
	rm -rf build/

# Build debug
debug:
	./cmake_configure_and_build.sh "debug"

# Build release
release:
	./cmake_configure_and_build.sh "release"

# Build a portable distribution of the executables and DLLs in a single dir
portable:
	./make_portable.sh "Client"
	./make_portable.sh "Server"
