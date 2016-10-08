#ifndef PERSONALASSISTANT_H
#define PERSONALASSISTANT_H

#include <QtWidgets/QDialog>

class PersonalAssistant : public QObject
{
	Q_OBJECT

public:
	PersonalAssistant(QWidget *parent = 0);
	~PersonalAssistant();
};

#endif // PERSONALASSISTANT_H
