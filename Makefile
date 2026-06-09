PREFIX ?= /usr/local

all: build

# Delegate to CMake's generated build system, which does correct incremental rebuilds and re-runs cmake itself whenever CMakeLists.txt changes.
# Our build/Makefile rule below only regenerates it when missing, i.e. the first build.
build: build/Makefile
	@$(MAKE) -C build

build/Makefile:
	@mkdir -p build && cd build && cmake ..

# Linux-only: macOS and Windows move the binary manually, for now.
install: build
	install -D -m 755 build/qt-remit $(PREFIX)/bin/qt-remit

test: build
	cd build && ctest --output-on-failure

.PHONY: all build install test
