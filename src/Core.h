/*
Core.h - User Interface Functions for the Maauw Extensions Pyrometer
Copyright (c) 2019 Syby Abraham.
*/

#ifndef Core_h
#define Core_h


#include "Arduino.h"
#include "SPI.h"
#include <SD.h>
#include "C:\Users\sybya\Documents\Arduino\maauw_extensions\MaauwE\src\MAX31855_STM32.h"

extern MAX31855_STM32 thermocouple;
extern Sd2Card card;
extern SdVolume volume;
extern SdFile root;

class Core {

public:

	Core();

	float tInt;

	float getTemp();
	float getVolt();

	void powerOff();
	void sdCardInfo();

	int tempChange();

	int tempRate();

private:
	int _state;
	int _rateState;
	int _tempSamples[2]; //Array to store sampled temperatures
	int _tempRate; //Array to store temperature differences
	int _rate; 
	unsigned long _clock;
	unsigned long _rateClock;
	float _temp;
	float _adcV;
	float _volt;
	float _vdd;
};
#endif