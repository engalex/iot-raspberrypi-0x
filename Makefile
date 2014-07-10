BUILDDIR=./bin
LIBDIR=~/iot-raspberrypi-0x/lib

all: clean build install

.PHONY: all build install clean

build: qsmain.cpp
	@echo "Copying required libraries..."
	@mkdir -p $(LIBDIR)
	@cp ./lib/libpaho-mqtt3as.so.1.0 $(LIBDIR)/libpaho-mqtt3as.so.1.0

	@echo "Creating symbolic links to libraries..."
	@ln -s libpaho-mqtt3as.so.1.0 $(LIBDIR)/libpaho-mqtt3as.so.1
	@ln -s libpaho-mqtt3as.so.1 $(LIBDIR)/libpaho-mqtt3as.so
	
	@echo "Compiling source code... (this may take some time)"
	@mkdir -p $(BUILDDIR)
	@g++ -std=c++0x *.cpp -Wall -o$(BUILDDIR)/iot-raspberrypi-0x -L $(LIBDIR) -I . -l paho-mqtt3as
	@echo "Build step completed."

install: build
	@cp -r ssl $(BUILDDIR)
	@echo "Install step completed."

clean:
	@echo "Clean..."
	@rm -rf $(BUILDDIR)
	@rm -rf $(LIBDIR)
	@echo "Clean step completed."