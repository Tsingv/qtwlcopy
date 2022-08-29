CC = g++
QTFLAGS = `pkg-config --cflags --libs Qt5Widgets`
CFLAGS = $(QTFLAGS) -fPIC

qtwlcopy:qtwlcopy.cpp
	$(CC) $(CFLAGS) -o qtwlcopy qtwlcopy.cpp

debug:qtwlcopy.cpp
	$(CC) $(CFLAGS) -g -o qtwlcopy qtwlcopy.cpp

.PHONY:install
install:
	@install -D ./qtwlcopy ~/.local/bin/qtwlcopy
	@echo "qtwlcopy has installed at ~/.local/bin/"

.PHONY:uninstall
uninstall:
	@rm -f ~/.local/bin/qtwlcopy
	@echo "qtwlcopy has been removed at ~/.local/bin/"
