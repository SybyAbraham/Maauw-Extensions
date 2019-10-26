// 
// 
// 

#include "Maauw.h"


void Maauw::run() {
	t.update();

	digitalWrite(PB4, HIGH);
	button.listen();

	if (button.isHold()) {
		ui.powerOff();
		powerOff();
	}
}