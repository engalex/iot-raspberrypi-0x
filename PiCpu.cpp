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
#include "PiCpu.h"

// PiCpu (Constructor)
// Constructs a PiCpu object, which calls the update method
// on construction.
PiCpu::PiCpu(void) {
	temperature = 0.0;
	load = 0.0;
	update();
}

PiCpu::~PiCpu(void) {

}

void PiCpu::update(void) {
	ifstream f(TEMPERATURE_FILE);
	std::string temperatureString, loadString;

	if(f.is_open()) {
		f >> temperatureString;
		temperature = stoi(temperatureString) / 1000.0;
		f.close();
	}

	f.open(LOAD_FILE);

	if(f.is_open()) {
		// Using the ifstream >> operator, we can
		// read the first load value, as the rest are
		// seperated by spaces (the stream operator tokenises
		// each line)
		stringstream ss;
		f >> loadString;
		// Put the string into the stringstream
		ss << loadString;
		// Stream into the double variable
		ss >> load;
		f.close();
	}
}

double PiCpu::getLoad(void) {
	return load;
}

double PiCpu::getTemperature(void) {
	return temperature;
}