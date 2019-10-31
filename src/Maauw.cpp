// 
// 
// 

#include "Maauw.h"


void Maauw::run() {

	button.listen();

	if (button.onPressAsToggle()) {
		ui.setUnit(0);
		_toggle = 0;
	}
	else {
		ui.setUnit(1);
		_toggle = 1;
	}

	if (_previousToggle != _toggle) {
		_previousToggle = _toggle;
		_powerSaveTimer = millis();
	}

	if (millis() - _powerSaveTimer > 150000) {
		ui.powerSave();
	}
	else if (millis() - _powerSaveTimer < 10) {
		ui.normal();
	}

	t.update();
	ui.run();

	if (ui.getDisplayState() == 3) {
		core.powerOff();
	}

	if (button.isHold()) {
		ui.powerOff();												//Set display/UI to Shutdown Screen
	}

	if (button.onDoubleClick()) {
		if (core.getCardState() == 1) {
			//Print "Please insert SD to start logging"
			ui.sdUI(1);
		} else if (core.getCardState() == 0){
			ui.sdUI(2);
			core.sdCardInfo();
		}
	}
}