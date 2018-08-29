// Oscilloscope.h

#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H
#include "Arduino.h"
#include "Button.h"

#define NCHANNELS 1
#define BAUDRATE 115200
#define LED 13

class Oscilloscope
{
private:
	bool sampling_on;  //True when sampling is on
	bool takeSample;
	bool timeOffset_go; //First timestamp is used to remove time offset
	unsigned long Time;
	unsigned long timeOffSet; //Time offset (Time = millis() - timeOffset)
	Button button;
	int SensorReading[NCHANNELS];
	const byte stop_message[2] = { 255, 253 };
	const byte pause_message[2] = { 255, 254 };
	const byte start_message[2] = { 255, 255 };
public:
	Oscilloscope(int buttonPin);
	
	void initializeSerial();

	void checkButton();
	
	void setTime();
	
	void setSensorReading(int channel, int value);
	
	void sendData();

	bool getSampling_on();

	void setTakeSample();

	bool getTakeSample();
};

#endif