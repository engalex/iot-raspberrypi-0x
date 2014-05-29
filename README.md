iot-raspberrypi-0x
==================
This repository currently stores a sample for connecting a Raspberry Pi Model B to the 
IBM Internet of Things Cloud 'Quickstart' service.

* __Compiled with:__ g++ (GCC) 4.8.2 20131219 (prerelease)
* __Tested on:__ Arch Linux ARM for Raspberry Pi.

__The build operations can be executed as a non-root user.__

Build with the following commands:
```
$ cd <directory>
$ make && . configure.sh
```

Run with the following command:
```
$ ./bin/iot-raspberrypi-0x
```

The sample will send one message per second, for one minute. To visualise the output
data, visit the [IBM Internet of Things Cloud Quickstart Portal](http://quickstart.internetofthings.ibmcloud.com/) and
enter your MAC address.
```
--- iot-raspberrypi-0x ---
Connecting...                   [ OK ]
Your MAC Address is: 
............................................................
Disconnecting...                [ OK ]
--- Sample finished. ---
```

__Note:__ This is not a fork of ibm-messaging/iot-raspberrypi repository due to a large number of differences in 
source material. However, this repository will produce similar results.

####Libraries
The required libraries (libpaho-mqtt3a and libmqttpp) are copied to ~/iot-raspberrypi-0x/lib
* [libpaho-mqtt3a](http://git.eclipse.org/c/paho/org.eclipse.paho.mqtt.c.git/) - Paho C Library for MQTT
* [libmqttpp](http://git.eclipse.org/c/paho/org.eclipse.paho.mqtt.cpp.git/): C++ Wrapper for Paho C Library
