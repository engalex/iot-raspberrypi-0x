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

#include "IOTClient.h"

using namespace std;

bool IOTClient::connected = false;

// IOTClient (Constructor)
// Constructs the IoT client, setting up an asynchronous
// MQTT client connection to the provided organization, with the
// provided device ID.
// @param deviceName 	- The name you wish to provide the service as an identifier.
// @param deviceId		- The device ID you wish to provide the service.
IOTClient::IOTClient(string organizationId, string deviceId) {
	int rc = MQTTASYNC_SUCCESS;
	string uri = organizationId + ".messaging.internetofthings.ibmcloud.com:1883";
	string clientId = "d:" + organizationId + ":iotsample-raspberrypi:" + deviceId;

	IOTClient::connected = false;

	opts = MQTTAsync_connectOptions_initializer;
	opts.keepAliveInterval = 20;
	opts.context = client;
	opts.onSuccess = &IOTClient::onConnect;

	MQTTAsync_create(&client, 
						(char*)uri.c_str(),
						(char*)clientId.c_str(),
						MQTTCLIENT_PERSISTENCE_NONE,
						NULL);

	MQTTAsync_setCallbacks(client, NULL, &IOTClient::connectionLost, NULL, NULL);

	if((rc = MQTTAsync_connect(client, &opts)) != MQTTASYNC_SUCCESS) {
		cout << "Connect error; return code: " << to_string(rc) << endl;
		exit(-1);
	} else {
		cout << "Client successfully connected." << endl;
	}
}

IOTClient::~IOTClient() {
	IOTClient::connected = false;
	MQTTAsync_destroy(&client);
}

void IOTClient::publish(string topic, string payload) {
	if(connected) {
		MQTTAsync_message message = MQTTAsync_message_initializer;
		int rc;
		
		message.payload = (char*)payload.c_str();
		message.payloadlen = payload.size();
		message.qos = 0;

		if ((rc = MQTTAsync_sendMessage(client, (char*)topic.c_str(), &message, NULL)) != MQTTASYNC_SUCCESS)
		{
			printf("Failed to start sendMessage, return code %d\n", rc);
	 		exit(-1);	
		}
	}
}

void IOTClient::connectionLost(void* context, char* cause) {
	cout << string(cause) << endl;
	IOTClient::connected = false;
}

void IOTClient::onConnect(void* context, MQTTAsync_successData* response) {
	IOTClient::connected = true;
}