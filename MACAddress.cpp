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
#include "MACAddress.h"
#include <iostream>

#define BUFFER_SIZE 1024

// MACAddress (Constructor)
// Determine the MAC Address of the machine. Stores
// the first HWAddr found. (If there are multiple)
MACAddress::MACAddress(void) {
	mac = "000000000000";
	interfaceName = "none";
	std::unique_ptr<char[]> buffer(new char[BUFFER_SIZE]);
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

	if(sock != -1 && buffer) {
		struct ifreq interfaceRecord;
		struct ifconf interfaceConfig;

		interfaceConfig.ifc_len = BUFFER_SIZE;
		interfaceConfig.ifc_buf = buffer.get();

		// Return a list of interfaces we can search
		if(ioctl(sock, SIOCGIFCONF, &interfaceConfig) != -1) {
			// Marks whether we have found a MAC Address
			bool success = false;
			struct ifreq* currentInterface = interfaceConfig.ifc_req;
			const struct ifreq* lastInterface = currentInterface + (interfaceConfig.ifc_len / sizeof(struct ifreq));

			while(currentInterface != lastInterface && !success) {
				std::strcpy(interfaceRecord.ifr_name, currentInterface->ifr_name);
				// Get the interface flags: if the interface is loopback
				// then don't continue.
				if(ioctl(sock, SIOCGIFFLAGS, &interfaceRecord) == 0 && !(interfaceRecord.ifr_flags & IFF_LOOPBACK)) {
					// Request the HWAddress / MAC Address
					if(ioctl(sock, SIOCGIFHWADDR, &interfaceRecord) == 0) {
						// Store the name of the interface
						interfaceName = std::string(interfaceRecord.ifr_name);
						success = true;
					}
				}
				currentInterface++;
			}

			if(success) {
				// Pull out the MAC address values, but do not
				// use seperators.
				mac = "";
				for(int i = 0; i < 6; i++) {
					std::stringstream s;
					s << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)interfaceRecord.ifr_hwaddr.sa_data[i];
					mac += s.str();
				}
			} else {
				std::cout << "Cannot find a HWAddr/MAC Address." << std::endl;
			}
		} else {
			std::cout << "No interfaces found." << std::endl;
		}
	} else {
		std::cout << "Cannot create socket." << std::endl;
	}
}

// MACAddress (Destructor)
// 
MACAddress::~MACAddress(void) {
	
}

// get
// Returns the MAC Address determined by the
// class constructor.
const std::string MACAddress::get(void) const {
	return mac;
}

// interface
// Returns the interface the MAC address belongs to.
const std::string MACAddress::getInterfaceName(void) const {
	return interfaceName;
}