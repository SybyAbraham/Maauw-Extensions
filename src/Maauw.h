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
#include "src\Core.h"
#include "src\UI.h"

extern Button button;
extern Timer t;

class Maauw : public UI, public Core{
public:
	void run();
private:
}

#endif

