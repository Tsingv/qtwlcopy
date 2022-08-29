CC = g++
QTFLAGS = `pkg-config --cflags --libs Qt5Widgets`
CFLAGS = $(QTFLAGS) -fPIC

qtwlcopy:qtwlcopy.cpp
	$(CC) $(CFLAGS) -o qtwlcopy qtwlcopy.cpp

.PHONY:install
install:
	@mkdir -p ~/.local/bin/
	@cp -f ./qtwlcopy ~/.local/bin/qtwlcopy
	@echo "qtwlcopy has installed at ~/.local/bin/"

.PHONY:uninstall
uninstall:
	@rm -f ~/.local/bin/qtwlcopy
	@echo "qtwlcopy has been removed at ~/.local/bin/"
