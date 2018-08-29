// 
// 
// 

#include "Button.h"

Button::Button(int pin)
	: pin(pin), prevState(false), timePressed(0)
{
	pinMode(pin, INPUT);
}

Button::buttonResult Button::input()
{
	state = (digitalRead(pin) == HIGH);
	if (state == prevState)
	{
		if (state) { return unchangedPressed; }
		else { return unchangedNotPressed; }
	}
	else
	{
		prevState = state;
		if (state) {
			timePressed = millis();
			return changedPressed;
		}
		else {
			unsigned long timeReleased = millis();
			if (timeReleased - timePressed > TIMELONGPRESS) //long press?
			{
				return longPressed;
			}
			else if (timeReleased - timePressed > TIMESHORTPRESS) //short press?
			{
				return shortPressed;
			}
			else
			{
				return debounce;
			}
		}
	}
}