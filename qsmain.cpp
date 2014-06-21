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
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <memory>
#include "QuickstartClient.h"
#include "MACAddress.h"
#include "PiCpu.h"

using namespace std;

#define PI 3.14159265

int main() {
	cout << "--- iot-raspberrypi-0x ---" << endl;
	shared_ptr<MACAddress> mac(new MACAddress());
	
	if(mac) {
		shared_ptr<QuickstartClient> client(new QuickstartClient("iot-raspberrypi-0x-sample", mac->get()));
		shared_ptr<PiCpu> cpu(new PiCpu());
		cout << "Your MAC Address is: " << mac->get() << std::endl;
		cout << "Network interface: " << mac->getInterfaceName() << std::endl;

		if(client) {
			// Run for 60 seconds
			for(int i = 0; i < 60; i++) {
				cpu->update();
				client->publish(cpu->getTemperature(), 
								cpu->getLoad(), 
								sin((i * 15) * (PI / 180)));
				// Sleep for one second
				std::this_thread::sleep_for(std::chrono::seconds(1));
				cout << "." << flush;
			}

			cout << endl;
		} else {
			cout << "Could not allocate enough memory for QuickstartClient." << endl;
		}
	}

	cout << "--- Sample finished. ---" << endl;
	return 0;
}