/********************************************************************************
** Form generated from reading UI file 'classbrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASSBROWSER_H
#define UI_CLASSBROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClassBrowser
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ClassBrowser)
    {
        if (ClassBrowser->objectName().isEmpty())
            ClassBrowser->setObjectName(QString::fromUtf8("ClassBrowser"));
        ClassBrowser->resize(800, 600);
        centralwidget = new QWidget(ClassBrowser);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 60, 113, 33));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(130, 60, 31, 31));
        ClassBrowser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ClassBrowser);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 27));
        ClassBrowser->setMenuBar(menubar);
        statusbar = new QStatusBar(ClassBrowser);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ClassBrowser->setStatusBar(statusbar);

        retranslateUi(ClassBrowser);

        QMetaObject::connectSlotsByName(ClassBrowser);
    } // setupUi

    void retranslateUi(QMainWindow *ClassBrowser)
    {
        ClassBrowser->setWindowTitle(QApplication::translate("ClassBrowser", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("ClassBrowser", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClassBrowser: public Ui_ClassBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSBROWSER_H
