/*
Name:       Oscilloscope.ino
Created:	27-Aug-18 3:54:01 PM
Author:     HPELITEBOOK\C. Reurslag

Description:	Can be used to monitor variables in real time using MATLAB. Max sampling frequency around 250Hz.
Need a button attached to pin D2(with 10K pulldown resistor)

*/


#include "Oscilloscope.h"
#define buttonPin 2

Oscilloscope oscilloscope(buttonPin);

void setup()
{
	oscilloscope.initializeSerial();

	//Create interrupt to handle button inputs
	pinMode(buttonPin, INPUT);
	attachInterrupt(digitalPinToInterrupt(buttonPin), buttonChanged, CHANGE);

	//Initialize timer1 
	noInterrupts();           //Disable all interrupts
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;

	OCR1A = 7999;            //Compare match register 16MHz/prescaler/frequency - 1 (must be <65536 for timer 1)
	TCCR1B |= (1 << WGM12);   //CTC mode
	TCCR1B |= (1 << CS11);    //prescaler of 8
	TIMSK1 |= (1 << OCIE1A);  //Enable timer compare interrupt
	interrupts();             //Enable all interrupts
}

void loop()
{
	if (oscilloscope.getTakeSample())
	{
		noInterrupts();
		oscilloscope.setSensorReading(0, analogRead(A0));
		oscilloscope.setTime();
		interrupts();
		oscilloscope.sendData();
	}
}


ISR(TIMER1_COMPA_vect)          //Timer compare interrupt service routine
{ //This function is called with a frequency of 2000 Hz
	oscilloscope.setTakeSample();
}

void buttonChanged()
{
	oscilloscope.checkButton();
}