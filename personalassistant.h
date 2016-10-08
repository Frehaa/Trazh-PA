#ifndef PERSONALASSISTANT_H
#define PERSONALASSISTANT_H

#include <QObject>

class PersonalAssistant : public QObject
{
	Q_OBJECT

public:
	PersonalAssistant(QObject *parent = 0);
	~PersonalAssistant();
};

#endif // PERSONALASSISTANT_H
