#pragma once

#include <QtWidgets/QDialog>
#include "ui_dialog_window.h"

class DialogWindow : public QDialog
{
	Q_OBJECT

public:
	DialogWindow(QWidget *parent = 0);
	~DialogWindow();
	void addItem(QString desc, QString tooltip, QString timer);
private:
	Ui::DialogWindow ui;
	unsigned rowCount;
};
