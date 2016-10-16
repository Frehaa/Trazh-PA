#pragma once

#include <Qtimer>

class ClockTimer
{
public:
	ClockTimer(int hours = 0, int minutes = 0, int seconds = 0, bool countingDown = true);
	~ClockTimer();

	QString getTimeQString();

	//	Sets the exact values for hours, minutes and seconds.
	//	Seconds and minutes have a max value of 59, everything above defaults to 59
	void setTime(int hours = 0, int minutes = 0, int seconds = 0);

	//	Boolean for choosing whether the clocks ticks up or down
	void setCountDown(bool countingDown);
	void start();
	void stop();
	
private:
	QTimer* timer;
	bool countdown;

	int hours;
	int minutes;
	int seconds;

	/* Functions handling decrementing of hours, minutes and seconds. Returns a boolean of whether or not decrementing happened. */
	bool decrementSeconds();
	bool decrementMinutes();
	bool decrementHours();
};