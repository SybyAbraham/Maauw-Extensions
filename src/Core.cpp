/*
Core.cpp - User Interface Functions for the Maauw Extensions Pyrometer
Copyright (c) 2019 Syby Abraham.
*/

#include "Core.h"

Core::Core() {
	_state = 1;
	_rateState = 1; 
}

float Core::getTemp() {

	//Measure only every 1.5 seconds
	
	switch (_state) {

		case 1:
			_temp = thermocouple.readInternal();
			_clock = millis(); 
			_state = 2;
			break;

		case 2:
			if (millis() - _clock > 1500) {

				_temp = thermocouple.readInternal();
				// reading Vdd by utilising the internal 1.20V VREF
				_vdd = 1.20 * 4096.0 / adc_read(ADC1, 17);
				_adcV = analogRead(PA1);
				_volt = _vdd * (_adcV / 4096); //Voltage Divider Battery Indicator								
				//Serial.println(_volt);
				//Serial.println(_vdd);
				_state = 1;		//Exit Machine
			}
	}
	return _temp;
}

int Core::tempChange() {

		switch (_rateState) {

			case 1:
				//Sample 1st temperature and store it in the array
					_tempSamples[0] = getTemp(); //Index 0
					_rateClock = millis();
					_rateState = 2;

			case 2:
				//Then wait a minute, get the next sample and add it to the array. 
				if (millis() - _rateClock > 60000) {
					_tempSamples[1] = getTemp(); //Index 1
					_rate = _tempSamples[1] - _tempSamples[0]; //Compute rate of change 
					_rateState = 1; 
				}
			}
			
	return _rate;
} 

int Core::tempRate() { //Rate Per hour
	_tempRate = tempChange() * 60; //tempChange() samples every minute so multiply by 60 to get rate per hour
	return _tempRate;
}

float Core::getVolt() {
	return _volt;
}

void Core::powerOff() {
	digitalWrite(PB5, LOW);
}

bool Core::getCardState() {
	return digitalRead(PB7);
}
void Core::sdCardInfo() {

	Serial.print("\nInitializing SD card...");

	// we'll use the initialization code from the utility libraries
	// since we're just testing if the card is working!
	if (!card.init(SPI_HALF_SPEED, PB12)) {
		Serial.println("initialization failed. Things to check:");
		Serial.println("* is a card inserted?");
		Serial.println("* is your wiring correct?");
		Serial.println("* did you change the chipSelect pin to match your shield or module?");
		while (1);
	}
	else {
		Serial.println("Wiring is correct and a card is present.");
	}

	// print the type of card
	Serial.println();
	Serial.print("Card type:         ");
	switch (card.type()) {
	case SD_CARD_TYPE_SD1:
		Serial.println("SD1");
		break;
	case SD_CARD_TYPE_SD2:
		Serial.println("SD2");
		break;
	case SD_CARD_TYPE_SDHC:
		Serial.println("SDHC");
		break;
	default:
		Serial.println("Unknown");
	}

	// Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
	if (!volume.init(card)) {
		Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
		while (1);
	}

	Serial.print("Clusters:          ");
	Serial.println(volume.clusterCount());
	Serial.print("Blocks x Cluster:  ");
	Serial.println(volume.blocksPerCluster());

	Serial.print("Total Blocks:      ");
	Serial.println(volume.blocksPerCluster() * volume.clusterCount());
	Serial.println();

	// print the type and size of the first FAT-type volume
	uint32_t volumesize;
	Serial.print("Volume type is:    FAT");
	Serial.println(volume.fatType(), DEC);

	volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
	volumesize *= volume.clusterCount();       // we'll have a lot of clusters
	volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
	Serial.print("Volume size (Kb):  ");
	Serial.println(volumesize);
	Serial.print("Volume size (Mb):  ");
	volumesize /= 1024;
	Serial.println(volumesize);
	Serial.print("Volume size (Gb):  ");
	Serial.println((float)volumesize / 1024.0);

	Serial.println("\nFiles found on the card (name, date and size in bytes): ");
	root.openRoot(volume);

	// list all files in the card with date and size
	root.ls(LS_R | LS_DATE | LS_SIZE);
}