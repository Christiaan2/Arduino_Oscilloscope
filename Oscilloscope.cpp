// 
// 
// 

#include "Oscilloscope.h"

Oscilloscope::Oscilloscope(int _buttonPin)
	: sampling_on(false), timeOffset_go(false), timeOffSet(0), button(_buttonPin)
{
	pinMode(LED, OUTPUT);
	digitalWrite(LED, sampling_on);
}

void Oscilloscope::initializeSerial()
{
	Serial.begin(BAUDRATE);
}

void Oscilloscope::checkButton()
{
	switch (button.input()) {
	case Button::longPressed:
	{//Stop Sampling and MATLAB script
		Serial.write(stop_message, 2);
		sampling_on = false;
		digitalWrite(LED, sampling_on);
	}
	break;
	case Button::shortPressed:
	{
		if (sampling_on)
		{ //Stop sampling
			Serial.write(pause_message, 2);
			sampling_on = false;
			digitalWrite(LED, sampling_on);
		}
		else
		{ //Start sampling
			timeOffset_go = true;
			Serial.write(start_message, 2);
			sampling_on = !sampling_on;
			digitalWrite(LED, sampling_on);
		}
	}
	break;
	}
}

void Oscilloscope::setTime()
{
	Time = millis(); //Time when sample was taken
	if (timeOffset_go) //First sample?
	{ //Yes, save time offset
		timeOffSet = Time;
		timeOffset_go = false;
	}
	Time = Time - timeOffSet; //Remove time offset
}

void Oscilloscope::setSensorReading(int channel, int value)
{
	SensorReading[channel] = value;
}

void Oscilloscope::sendData()
{
	for (int i = 0; i < NCHANNELS; i++)
	{
		byte SensorReading_byte[2] = { SensorReading[i], SensorReading[i] >> 8 };
		Serial.write(SensorReading_byte, 2); //Send sensor value to pc
	}
	byte Time_byte[4] = { Time, Time >> 8, Time >> 16, Time >> 24 };
	Serial.write(Time_byte, 4); //Send time to pc
}

bool Oscilloscope::getSampling_on()
{
	return sampling_on;
}

void Oscilloscope::setTakeSample()
{
	this->takeSample = sampling_on;
}

bool Oscilloscope::getTakeSample()
{
	if (takeSample)
	{
		takeSample = false;
		return true;
	}
	else
	{
		return false;

	}
}