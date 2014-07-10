iot-raspberrypi-0x
==================
This repository currently stores a sample for connecting a Raspberry Pi Model B to the 
IBM Internet of Things Cloud 'Quickstart' service.

* __Compiled with:__ g++ (GCC) 4.8.2 20131219 (prerelease)
* __Tested on:__ Arch Linux ARM for Raspberry Pi.

__The build operations and program can be executed as a non-root user.__

Build with the following commands:
```
$ cd <directory>
$ make && . configure.sh
```

####Quickstart Service
Run with the following command:
```
$ ./bin/iot-raspberrypi-0x -q
```

Run the pre-built binary with the following command:
```
$ ./pre-built/iot-raspberrypi-0x-arch -q
```

The sample will send one message per second, for one minute. To visualise the output
data, visit the [IBM Internet of Things Cloud Quickstart Portal](http://quickstart.internetofthings.ibmcloud.com/) and
enter your MAC address.
```
--- iot-raspberrypi-0x ---
Connecting...                   [ OK ]
Your MAC Address is: 12345678990AB
Network Interface: wlan0
............................................................
Disconnecting...                [ OK ]
--- Sample finished. ---
```

####Beta Service
The IoT Cloud Beta Service implementation is a work-in-progress. Stay tuned!

Run with the following command:
```
$ ./bin/iot-raspberrypi-0x
```

__Note:__ This is not a fork of ibm-messaging/iot-raspberrypi repository due to a large number of differences in 
source material. However, this repository will produce similar results.

####Libraries
The required library, libpaho-mqtt3as is copied to ~/iot-raspberrypi-0x/lib
* [libpaho-mqtt3a](http://git.eclipse.org/c/paho/org.eclipse.paho.mqtt.c.git/) - Paho C Library for MQTT (Asynchronous and Secure)
