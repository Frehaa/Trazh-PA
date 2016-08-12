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
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_PersonalAssistantClass
{
public:

    void setupUi(QDialog *PersonalAssistantClass)
    {
        if (PersonalAssistantClass->objectName().isEmpty())
            PersonalAssistantClass->setObjectName(QStringLiteral("PersonalAssistantClass"));
        PersonalAssistantClass->resize(600, 400);

        retranslateUi(PersonalAssistantClass);

        QMetaObject::connectSlotsByName(PersonalAssistantClass);
    } // setupUi

    void retranslateUi(QDialog *PersonalAssistantClass)
    {
        PersonalAssistantClass->setWindowTitle(QApplication::translate("PersonalAssistantClass", "PersonalAssistant", 0));
    } // retranslateUi

};

namespace Ui {
    class PersonalAssistantClass: public Ui_PersonalAssistantClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONALASSISTANT_H
