#pragma once

#include <QLabel>
#include <QTimer>

class TimerLabel : public QLabel
{
	Q_OBJECT;

public:
	TimerLabel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	//TimerLabel(Timer timer, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

private:
	QTimer timer;



};