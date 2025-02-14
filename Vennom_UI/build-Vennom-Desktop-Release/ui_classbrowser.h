/********************************************************************************
** Form generated from reading UI file 'classbrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASSBROWSER_H
#define UI_CLASSBROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClassBrowser
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ClassBrowser)
    {
        if (ClassBrowser->objectName().isEmpty())
            ClassBrowser->setObjectName(QStringLiteral("ClassBrowser"));
        ClassBrowser->resize(800, 600);
        menubar = new QMenuBar(ClassBrowser);
        menubar->setObjectName(QStringLiteral("menubar"));
        ClassBrowser->setMenuBar(menubar);
        centralwidget = new QWidget(ClassBrowser);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        ClassBrowser->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ClassBrowser);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ClassBrowser->setStatusBar(statusbar);

        retranslateUi(ClassBrowser);

        QMetaObject::connectSlotsByName(ClassBrowser);
    } // setupUi

    void retranslateUi(QMainWindow *ClassBrowser)
    {
        ClassBrowser->setWindowTitle(QApplication::translate("ClassBrowser", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class ClassBrowser: public Ui_ClassBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSBROWSER_H
