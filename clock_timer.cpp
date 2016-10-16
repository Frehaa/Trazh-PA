#include "clock_timer.h"

ClockTimer::ClockTimer(int hours, int minutes, int seconds, bool countingDown)
{
	timer = new QTimer();
	setTime(hours, minutes, seconds);
}

ClockTimer::~ClockTimer()
{
	delete timer;
}

QString ClockTimer::getTimeQString()
{
	QString timeString = QString("%1h %2m %3s").arg(hours, minutes, seconds);
	return timeString;
}

void ClockTimer::setTime(int hours, int minutes, int seconds)
{
	this->seconds = seconds % 60;
	this->minutes = minutes % 60;
	this->hours = hours;
}

void ClockTimer::setCountDown(bool countingDown)
{
	this->countdown = countdown;
}

void ClockTimer::start()
{
	timer->start();
}

void ClockTimer::stop()
{
	timer->stop();
}

bool ClockTimer::decrementSeconds()
{
	if (seconds == 0)
	{
		if (decrementMinutes())
			seconds = 59;
		else
			return false;
	}
	else
	{
		--seconds;
	}
	
	return true;
}

bool ClockTimer::decrementMinutes()
{
	if (minutes == 0)
	{
		if (decrementHours())
			minutes = 59;
		else
			return false;
	}
	else
	{
		--minutes;
	}
	
	return true;

}

bool ClockTimer::decrementHours()
{
	if (hours > 0)
	{
		--hours;
		return true;
	}

	return false;

}
