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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VennomUI
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QListWidget *listWidget;
    QTreeWidget *ion_tree;
    QPushButton *WriteIonButton;
    QPushButton *Add_Param_Button;
    QPushButton *Add_State_Button;
    QPushButton *Add_Dep_Button;
    QPushButton *End_State_Button;
    QPushButton *iDelete_Button;
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
        tabWidget->setGeometry(QRect(10, 0, 961, 541));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(30, 50, 256, 411));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        ion_tree = new QTreeWidget(tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(2, QStringLiteral("3"));
        __qtreewidgetitem->setText(1, QStringLiteral("2"));
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        ion_tree->setHeaderItem(__qtreewidgetitem);
        ion_tree->setObjectName(QStringLiteral("ion_tree"));
        ion_tree->setGeometry(QRect(320, 50, 611, 411));
        ion_tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ion_tree->setColumnCount(3);
        WriteIonButton = new QPushButton(tab);
        WriteIonButton->setObjectName(QStringLiteral("WriteIonButton"));
        WriteIonButton->setGeometry(QRect(110, 470, 95, 31));
        Add_Param_Button = new QPushButton(tab);
        Add_Param_Button->setObjectName(QStringLiteral("Add_Param_Button"));
        Add_Param_Button->setGeometry(QRect(680, 10, 111, 31));
        Add_State_Button = new QPushButton(tab);
        Add_State_Button->setObjectName(QStringLiteral("Add_State_Button"));
        Add_State_Button->setGeometry(QRect(320, 10, 95, 31));
        Add_Dep_Button = new QPushButton(tab);
        Add_Dep_Button->setObjectName(QStringLiteral("Add_Dep_Button"));
        Add_Dep_Button->setGeometry(QRect(800, 10, 121, 31));
        End_State_Button = new QPushButton(tab);
        End_State_Button->setObjectName(QStringLiteral("End_State_Button"));
        End_State_Button->setGeometry(QRect(420, 10, 131, 31));
        iDelete_Button = new QPushButton(tab);
        iDelete_Button->setObjectName(QStringLiteral("iDelete_Button"));
        iDelete_Button->setGeometry(QRect(570, 10, 95, 31));
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
        WriteIonButton->setText(QApplication::translate("VennomUI", "Write to File", 0));
        Add_Param_Button->setText(QApplication::translate("VennomUI", "New Parameter", 0));
        Add_State_Button->setText(QApplication::translate("VennomUI", "New State", 0));
        Add_Dep_Button->setText(QApplication::translate("VennomUI", "Add Dependency", 0));
        End_State_Button->setText(QApplication::translate("VennomUI", "End Current State", 0));
        iDelete_Button->setText(QApplication::translate("VennomUI", "Delete ", 0));
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
