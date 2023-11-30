/********************************************************************************
** Form generated from reading UI file 'CppNumercialSolvers_Visualized.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPPNUMERCIALSOLVERS_VISUALIZED_H
#define UI_CPPNUMERCIALSOLVERS_VISUALIZED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CppNumercialSolvers_VisualizedClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CppNumercialSolvers_VisualizedClass)
    {
        if (CppNumercialSolvers_VisualizedClass->objectName().isEmpty())
            CppNumercialSolvers_VisualizedClass->setObjectName(QString::fromUtf8("CppNumercialSolvers_VisualizedClass"));
        CppNumercialSolvers_VisualizedClass->resize(600, 400);
        menuBar = new QMenuBar(CppNumercialSolvers_VisualizedClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        CppNumercialSolvers_VisualizedClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CppNumercialSolvers_VisualizedClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CppNumercialSolvers_VisualizedClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CppNumercialSolvers_VisualizedClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        CppNumercialSolvers_VisualizedClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CppNumercialSolvers_VisualizedClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CppNumercialSolvers_VisualizedClass->setStatusBar(statusBar);

        retranslateUi(CppNumercialSolvers_VisualizedClass);

        QMetaObject::connectSlotsByName(CppNumercialSolvers_VisualizedClass);
    } // setupUi

    void retranslateUi(QMainWindow *CppNumercialSolvers_VisualizedClass)
    {
        CppNumercialSolvers_VisualizedClass->setWindowTitle(QCoreApplication::translate("CppNumercialSolvers_VisualizedClass", "CppNumercialSolvers_Visualized", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CppNumercialSolvers_VisualizedClass: public Ui_CppNumercialSolvers_VisualizedClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPPNUMERCIALSOLVERS_VISUALIZED_H
