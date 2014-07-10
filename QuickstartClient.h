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
 
#include "IOTClient.h"

using namespace std;

class QuickstartClient : public IOTClient {
private:
	string myName;
public:
	QuickstartClient(string organizationId, string macAddress);
	~QuickstartClient();
	void publish(double cpuTemperature, double cpuLoad, double sine);
};