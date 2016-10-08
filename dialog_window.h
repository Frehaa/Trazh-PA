#pragma once

#include <QtWidgets/QDialog>

class DialogWindow : public QDialog
{
	Q_OBJECT

public:
	DialogWindow(QWidget *parent = 0);
	~DialogWindow();

private:
	int i;
};
