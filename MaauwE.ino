#include "src\UI.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <SD.h>
#include "Button.h"
#include <Timer.h>

#include "src\MAX31855_STM32.h"
#include "src\Core.h"
#include "src\Maauw.h"

U8G2_SSD1327_MIDAS_128X128_F_4W_HW_SPI u8g2(U8G2_R0, PB0, PB1, 8);
MAX31855_STM32 thermocouple(PA8, PA9, PA10);

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

OrtonCones cone;
Maauw maauw;

Timer t;

#define btn PB3
  
int loader = 60;

double temp = 0; 
int temp1; 
int state = LOW;      // the current state of the output pin
int previous = LOW;    // the previous reading from the input pin
bool ledState;
float volt;

bool previousDR; 

bool callback = 0;

Button button = Button(PB4, LOW);

void setup(void) {
	pinMode(PB7, INPUT_PULLUP);
	pinMode(PB5, OUTPUT);
	digitalWrite(PB5, HIGH);
	pinMode(PB4, INPUT_PULLUP); //Push button

	digitalWrite(PC13, LOW);

	button.setHoldDelay(2500);
	button.setDebounceDelay(55);

	Serial.begin(9600);
	Serial.println("Serial is active");

	u8g2.clearBuffer();
	u8g2.begin();
	button.listen();
	u8g2.setBusClock(32000000);

	for (loader; loader < 104; loader += 2) {
		  maauw.loader(loader);
	}

	delay(1000);
	u8g2.clearBuffer(); 
}

void loop(void) {    
	maauw.run();
}

