BUILDDIR=./bin
LIBDIR=~/iot-raspberrypi-0x/lib

all: clean build install

.PHONY: all build install clean

build: qsmain.cpp
	@echo "Copying required libraries..."
	@mkdir -p $(LIBDIR)
	@cp ./lib/libpaho-mqtt3a.so.1.0 $(LIBDIR)/libpaho-mqtt3a.so.1.0
	@cp ./lib/libmqttpp.so.0.1 $(LIBDIR)/libmqttpp.so.0.1

	@echo "Creating symbolic links to libraries..."
	@ln -s libpaho-mqtt3a.so.1.0 $(LIBDIR)/libpaho-mqtt3a.so.1
	@ln -s libpaho-mqtt3a.so.1 $(LIBDIR)/libpaho-mqtt3a.so
	@ln -s libmqttpp.so.0.1 $(LIBDIR)/libmqttpp.so.0
	@ln -s libmqttpp.so.0 $(LIBDIR)/libmqttpp.so
	
	@echo "Compiling source code... (this may take some time)"
	@mkdir -p $(BUILDDIR)
	@g++ -std=c++0x *.cpp -Wall -o$(BUILDDIR)/iot-raspberrypi-0x -L $(LIBDIR) -I . -l paho-mqtt3a -l mqttpp
	@echo "Build step completed."

install: build
	@echo "Install step completed."

clean:
	@echo "Clean..."
	@rm -rf $(BUILDDIR)
	@rm -rf $(LIBDIR)
	@echo "Clean step completed."