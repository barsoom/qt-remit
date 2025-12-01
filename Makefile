PREFIX ?= /usr/local

build/qt-remit:
	@mkdir -p build && cd build && cmake .. && make

all: build/qt-remit

install: build/qt-remit
	install -D -m 755 build/qt-remit $(PREFIX)/bin/qt-remit
