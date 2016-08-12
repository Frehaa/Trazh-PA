#ifndef PERSONALASSISTANT_H
#define PERSONALASSISTANT_H

#include <QtWidgets/QDialog>
#include "ui_personalassistant.h"

class PersonalAssistant : public QDialog
{
	Q_OBJECT

public:
	PersonalAssistant(QWidget *parent = 0);
	~PersonalAssistant();

private:
	Ui::PersonalAssistantClass ui;
};

#endif // PERSONALASSISTANT_H
