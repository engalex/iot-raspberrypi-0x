/*******************************************************************************
 * Copyright (c) 2014 Niall Frederick Weedon and other Contributors
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Niall Frederick Weedon - Initial Contribution
 *******************************************************************************/ 
#include "QuickstartClient.h"

using namespace std;

// QuickstartClient (Constructor)
// Constructs the quickstart client, setting up an asynchronous
// MQTT client connection to the Quickstart service and the topic
// string to be used when publishing.
// @param deviceName 	- The name you wish to provide the service as an identifier.
// @param macAddress	- The MAC Address you wish to provide the service.
QuickstartClient::QuickstartClient(string deviceName, string macAddress) : IOTClient("quickstart", macAddress) {
	myName = deviceName;
}

// QuickstartClient (Destructor)
// Destructs the Quickstart client, in this case, disconnecting
// the client if it is connected and releasing the resources used
// by it.
QuickstartClient::~QuickstartClient(void) {

}

// publish
// Publish a Raspberry Pi quickstart message.
// @param cpuTemperature
// @param cpuLoad
// @param sine
void QuickstartClient::publish(double cpuTemperature, double cpuLoad, double sine) {
	// Construct the Quickstart message.
	string payload = std::string("{\"d\":{ \"cputemp\":" + std::to_string(cpuTemperature));
	payload += std::string(", \"cpuload\":" + std::to_string(cpuLoad));
	payload += std::string(", \"sine\":" + std::to_string(sine));
	payload += std::string(", \"myName\": \"" + myName + "\" } }");
	// Call base publishing function.
	IOTClient::publish(string("iot-2/evt/status/fmt/json"), payload);
}