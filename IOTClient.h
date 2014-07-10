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
#pragma once

extern "C" {
	#include "mqtt/MQTTAsync.h"
	#include "mqtt/MQTTClientPersistence.h"
}

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class IOTClient {
	private:
		MQTTAsync_connectOptions opts;
	protected:
		MQTTAsync client;
		static bool connected;
		static void connectionLost(void* context, char* cause);
		static void onConnect(void* context, MQTTAsync_successData* response);
	public:
		IOTClient(string organizationId, string macAddress);
		~IOTClient();
		void publish(string topic, string payload);
};