#ifndef PERSONALASSISTANT_H
#define PERSONALASSISTANT_H

#include <QtWidgets/QMainWindow>
#include "ui_personalassistant.h"

class PersonalAssistant : public QMainWindow
{
	Q_OBJECT

public:
	PersonalAssistant(QWidget *parent = 0);
	~PersonalAssistant();

private:
	Ui::PersonalAssistantClass ui;
};

#endif // PERSONALASSISTANT_H
