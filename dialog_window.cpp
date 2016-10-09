#include "dialog_window.h"

DialogWindow::DialogWindow(QWidget *parent)
	: QDialog(parent, Qt::FramelessWindowHint), rowCount(1)
{
	this->setAttribute(Qt::WA_TranslucentBackground);
	ui.setupUi(this);
	ui.headerLabel->setText("WARFRAME ALERTS");

	
	addItem("Testin", "Hey", "12323 o'clock");
	addItem("Hey", "Hello", "It'll go");
	addItem("And", "All", "tha' jazz");
	this->show();
}
DialogWindow::~DialogWindow()
{}

void DialogWindow::addItem(QString desc, QString tooltip, QString timer)
{
	
	QFont font1;
	font1.setFamily(QStringLiteral("Verdana"));

	QLabel* descriptionLabel = new QLabel(ui.itemList);	
	descriptionLabel->setText(desc);
	descriptionLabel->setToolTip(tooltip);

	descriptionLabel->setMinimumSize(QSize(250, 25));
	descriptionLabel->setMaximumSize(QSize(250, 25));
	descriptionLabel->setFont(font1);
	descriptionLabel->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
	descriptionLabel->setWordWrap(false);
	descriptionLabel->setIndent(5);

	ui.formLayout->setWidget(rowCount, QFormLayout::LabelRole, descriptionLabel);

	QFont font2;
	font2.setFamily(QStringLiteral("Verdana"));
	font2.setItalic(true);

	QLabel* timeLabel = new QLabel(ui.itemList);
	timeLabel->setText(timer);
	timeLabel->setMinimumSize(QSize(90, 25));
	timeLabel->setMaximumSize(QSize(90, 25));
	timeLabel->setFont(font2);
	timeLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
	timeLabel->setWordWrap(false);
	timeLabel->setIndent(5);

	ui.formLayout->setWidget(rowCount, QFormLayout::FieldRole, timeLabel);

	++rowCount;
}

