/********************************************************************************
** Form generated from reading UI file 'vennomui.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENNOMUI_H
#define UI_VENNOMUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VennomUI
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QListWidget *listWidget;
    QWidget *tab_2;
    QWidget *tab_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VennomUI)
    {
        if (VennomUI->objectName().isEmpty())
            VennomUI->setObjectName(QStringLiteral("VennomUI"));
        VennomUI->resize(981, 606);
        VennomUI->setDocumentMode(true);
        VennomUI->setTabShape(QTabWidget::Triangular);
        centralWidget = new QWidget(VennomUI);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 781, 411));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(30, 50, 256, 441));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());
        VennomUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VennomUI);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 981, 27));
        VennomUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VennomUI);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VennomUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VennomUI);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VennomUI->setStatusBar(statusBar);

        retranslateUi(VennomUI);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(VennomUI);
    } // setupUi

    void retranslateUi(QMainWindow *VennomUI)
    {
        VennomUI->setWindowTitle(QApplication::translate("VennomUI", "VennomUI", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("VennomUI", "Channel Designer", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("VennomUI", "Neuron Designer", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("VennomUI", "Network Configurator", 0));
    } // retranslateUi

};

namespace Ui {
    class VennomUI: public Ui_VennomUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENNOMUI_H
