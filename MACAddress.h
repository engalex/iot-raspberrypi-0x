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
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>

class MACAddress {
private:
	std::string mac, interfaceName;
public:
	MACAddress(void);
	~MACAddress(void);
	const std::string get(void) const;
	const std::string getInterfaceName(void) const;
};