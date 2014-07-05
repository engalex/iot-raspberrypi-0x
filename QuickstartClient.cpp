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

// QuickstartClient (Constructor)
// Constructs the quickstart client, setting up an asynchronous
// MQTT client connection to the Quickstart service and the topic
// string to be used when publishing.
// @param deviceName 	- The name you wish to provide the service as an identifier.
// @param macAddress	- The MAC Address you wish to provide the service.
QuickstartClient::QuickstartClient(std::string deviceName, std::string macAddress) {
	client = std::unique_ptr<mqtt::async_client>(new mqtt::async_client("quickstart.messaging.internetofthings.ibmcloud.com:1883", 
																		"d:quickstart:iotsample-raspberrypi:" + macAddress));
	topic = std::string("iot-2/evt/status/fmt/json");
	myName = deviceName;

	if(client) {
		ClientCallback cb;
		client->set_callback(cb);

		connect();
	}
}

// QuickstartClient (Destructor)
// Destructs the Quickstart client, in this case, disconnecting
// the client if it is connected and releasing the resources used
// by it.
QuickstartClient::~QuickstartClient(void) {
	disconnect();
}

// connect
// Connects to the MQTT Service.
void QuickstartClient::connect(void) {
	if(client) {
		std::cout << "Connecting..." << std::flush;
		// Connect to the service asynchronously and wait
		// for the connection to complete.
		connectionToken = client->connect();
		connectionToken->wait_for_completion();
		std::cout << "\t\t\t[ OK ]" << std::endl;
	}
}

// disconnect
// Disconnects from the MQTT Service.
void QuickstartClient::disconnect(void) {
	if(client) {
		std::cout << "Disconnecting..." << std::flush;
		// Disconnect asynchronously and wait for its
		// completion.
		connectionToken = client->disconnect();
		connectionToken->wait_for_completion();
		std::cout << "\t\t[ OK ]" << std::endl;
	}
}

// publish
// Publish a Raspberry Pi quickstart message.
// @param cpuTemperature
// @param cpuLoad
// @param sine
void QuickstartClient::publish(double cpuTemperature, double cpuLoad, double sine) {
	if(client) {
		std::string payload = std::string("{\"d\":{ \"cputemp\":" + std::to_string(cpuTemperature));
		payload += std::string(", \"cpuload\":" + std::to_string(cpuLoad));
		payload += std::string(", \"sine\":" + std::to_string(sine));
		payload += std::string(", \"myName\": \"" + myName + "\" } }");

		mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(payload.c_str());
		pubmsg->set_qos(0);
		client->publish(topic, pubmsg)->wait_for_completion(TIMEOUT);
	}
}

// connection_lost
// Event fired when the client unexpectedly loses
// connection from the service.
void QuickstartClient::ClientCallback::connection_lost(const std::string& cause) {
	std::cout << "\nConnection lost." << std::endl;
	if (!cause.empty())
		std::cout << "\tCause: " << cause << std::endl;
}

// delivery_complete
// Event fired when the client successfully publishes
// a message.
void QuickstartClient::ClientCallback::delivery_complete(mqtt::idelivery_token_ptr tok) {
	
}

// message_arrived
// Event fired when the client receives a message.
void QuickstartClient::ClientCallback::message_arrived(const std::string& topic, mqtt::message_ptr msg) {

}