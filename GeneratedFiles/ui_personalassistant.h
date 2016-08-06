/********************************************************************************
** Form generated from reading UI file 'personalassistant.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONALASSISTANT_H
#define UI_PERSONALASSISTANT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PersonalAssistantClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PersonalAssistantClass)
    {
        if (PersonalAssistantClass->objectName().isEmpty())
            PersonalAssistantClass->setObjectName(QStringLiteral("PersonalAssistantClass"));
        PersonalAssistantClass->resize(600, 400);
        menuBar = new QMenuBar(PersonalAssistantClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        PersonalAssistantClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PersonalAssistantClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PersonalAssistantClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PersonalAssistantClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PersonalAssistantClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PersonalAssistantClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PersonalAssistantClass->setStatusBar(statusBar);

        retranslateUi(PersonalAssistantClass);

        QMetaObject::connectSlotsByName(PersonalAssistantClass);
    } // setupUi

    void retranslateUi(QMainWindow *PersonalAssistantClass)
    {
        PersonalAssistantClass->setWindowTitle(QApplication::translate("PersonalAssistantClass", "PersonalAssistant", 0));
    } // retranslateUi

};

namespace Ui {
    class PersonalAssistantClass: public Ui_PersonalAssistantClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONALASSISTANT_H
