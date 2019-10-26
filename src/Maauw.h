// Maauw.h


#ifndef _MAAUW_h
#define _MAAUW_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Button.h"
#include <Timer.h>
#include "C:\Users\sybya\Documents\Arduino\maauw_extensions\Maauw-Extensions\src\Core.h"
#include "C:\Users\sybya\Documents\Arduino\maauw_extensions\Maauw-Extensions\src\UI.h"

extern Button button;
extern Timer t;


class Maauw : public UI {
public:
	void run();
private:
	UI ui;
	bool _toggle = 0;
	bool _previousToggle;
	unsigned long _powerSaveTimer;
};

#endif

