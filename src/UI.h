/*
UI.h - User Interface Functions for the Maauw Extensions Pyrometer
Copyright (c) 2019 Syby Abraham.
*/

#ifndef UI_h
#define UI_h

#include "Arduino.h"
#include "U8g2lib.h"
#include "C:\Users\sybya\Documents\Arduino\maauw_extensions\MaauwE\src\OrtonCones.h"
#include "C:\Users\sybya\Documents\Arduino\maauw_extensions\MaauwE\src\Core.h"

#define cone_width 29
#define cone_height 38

#define maauw_ext_width 120
#define maauw_ext_height 34

#define alpha_width 8
#define alpha_height 8

#define beta_width 8
#define beta_height 14

#define fire_width 8
#define fire_height 28

#define frameRate 35

extern U8G2_SSD1327_MIDAS_128X128_F_4W_HW_SPI u8g2;

class UI : public Core{
public:

	UI();

	int center(char input[]);
	void convertToChar(String str, char outChar[]);
	void createPopup(char msg[], int duration);
	void sdPopupHandler();
	void shutdownScreen();
	void displayCone();
	void battIcon();
	void showTemp(bool mode);
	void loader(int load);
	void run(void);
	void fireAnimation(int x, int y);

	void powerOff(void); 
	void powerSave();
	void normal();

	int getDisplayState();

	int setUnit(int unit);
	int getUnit();

	Core core;

	static int ptest;

private:
	int _state;
	int _animFrame; 
	unsigned long _time; 
	unsigned long _animClock;
	bool _prevDR;
	bool _unit;
	int _callback;
	int charge = 0;
	int _displayState = 2; 
	

	static const unsigned char PROGMEM maauw_ext_bits[];
	static const unsigned char PROGMEM cone_bits[];
	static const unsigned char PROGMEM alpha_bits[];
	static const unsigned char PROGMEM beta_bits[];

	//Fire Animation
	static const unsigned char fire_01_bits[] U8X8_PROGMEM;
	static const unsigned char fire_02_bits[] U8X8_PROGMEM;
	static const unsigned char fire_03_bits[] U8X8_PROGMEM;
	static const unsigned char fire_04_bits[] U8X8_PROGMEM;
	static const unsigned char fire_05_bits[] U8X8_PROGMEM;
	static const unsigned char fire_06_bits[] U8X8_PROGMEM;
	static const unsigned char fire_07_bits[] U8X8_PROGMEM;
	static const unsigned char fire_08_bits[] U8X8_PROGMEM;
	static const unsigned char fire_09_bits[] U8X8_PROGMEM;
	static const unsigned char fire_10_bits[] U8X8_PROGMEM;
	static const unsigned char fire_11_bits[] U8X8_PROGMEM;
	static const unsigned char fire_12_bits[] U8X8_PROGMEM;
	
	OrtonCones cone;
};

#endif