// Button.h

#ifndef BUTTON_H
#define BUTTON_H
#include "Arduino.h"

#define TIMESHORTPRESS 5
#define TIMELONGPRESS 1000

class Button
{
private:
	int pin;
	bool state;
	bool prevState;
	unsigned long timePressed;
public:
	enum buttonResult { unchangedPressed, unchangedNotPressed, changedPressed, shortPressed, longPressed, debounce };
	Button(int pin);

	buttonResult input();
};

#endif