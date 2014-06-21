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
#include <fstream>
#include <iostream>
#include <sstream>

#define TEMPERATURE_FILE "/sys/class/thermal/thermal_zone0/temp"
#define LOAD_FILE "/proc/loadavg"

using namespace std;

class PiCpu {
	private:
		double load, temperature;
	public:
		PiCpu(void);
		~PiCpu(void);
		void update(void);
		double getLoad(void);
		double getTemperature(void);
};