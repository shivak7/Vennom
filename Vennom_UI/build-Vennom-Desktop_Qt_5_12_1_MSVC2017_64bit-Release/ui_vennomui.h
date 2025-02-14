/********************************************************************************
** Form generated from reading UI file 'vennomui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENNOMUI_H
#define UI_VENNOMUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QPushButton *Add_State_Button;
    QPushButton *End_State_Button;
    QPushButton *iDelete_Button;
    QPushButton *Add_Param_Button;
    QPushButton *Add_Dep_Button;
    QListWidget *listWidget;
    QTreeWidget *ion_tree;
    QPushButton *WriteIonButton;
    QWidget *tab_2;
    QWidget *tab_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VennomUI)
    {
        if (VennomUI->objectName().isEmpty())
            VennomUI->setObjectName(QString::fromUtf8("VennomUI"));
        VennomUI->resize(997, 607);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VennomUI->sizePolicy().hasHeightForWidth());
        VennomUI->setSizePolicy(sizePolicy);
        VennomUI->setDocumentMode(true);
        VennomUI->setTabShape(QTabWidget::Triangular);
        centralWidget = new QWidget(VennomUI);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(5);
        sizePolicy2.setVerticalStretch(5);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        Add_State_Button = new QPushButton(tab);
        Add_State_Button->setObjectName(QString::fromUtf8("Add_State_Button"));

        gridLayout_2->addWidget(Add_State_Button, 0, 1, 1, 1);

        End_State_Button = new QPushButton(tab);
        End_State_Button->setObjectName(QString::fromUtf8("End_State_Button"));

        gridLayout_2->addWidget(End_State_Button, 0, 2, 1, 1);

        iDelete_Button = new QPushButton(tab);
        iDelete_Button->setObjectName(QString::fromUtf8("iDelete_Button"));

        gridLayout_2->addWidget(iDelete_Button, 0, 3, 1, 1);

        Add_Param_Button = new QPushButton(tab);
        Add_Param_Button->setObjectName(QString::fromUtf8("Add_Param_Button"));

        gridLayout_2->addWidget(Add_Param_Button, 0, 4, 1, 1);

        Add_Dep_Button = new QPushButton(tab);
        Add_Dep_Button->setObjectName(QString::fromUtf8("Add_Dep_Button"));

        gridLayout_2->addWidget(Add_Dep_Button, 0, 5, 1, 1);

        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(listWidget, 1, 0, 1, 1);

        ion_tree = new QTreeWidget(tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(2, QString::fromUtf8("3"));
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        ion_tree->setHeaderItem(__qtreewidgetitem);
        ion_tree->setObjectName(QString::fromUtf8("ion_tree"));
        ion_tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ion_tree->setColumnCount(3);

        gridLayout_2->addWidget(ion_tree, 1, 1, 1, 5);

        WriteIonButton = new QPushButton(tab);
        WriteIonButton->setObjectName(QString::fromUtf8("WriteIonButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(5);
        sizePolicy3.setVerticalStretch(5);
        sizePolicy3.setHeightForWidth(WriteIonButton->sizePolicy().hasHeightForWidth());
        WriteIonButton->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(WriteIonButton, 2, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        VennomUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VennomUI);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 997, 21));
        VennomUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VennomUI);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        VennomUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VennomUI);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        VennomUI->setStatusBar(statusBar);

        retranslateUi(VennomUI);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(VennomUI);
    } // setupUi

    void retranslateUi(QMainWindow *VennomUI)
    {
        VennomUI->setWindowTitle(QApplication::translate("VennomUI", "VennomUI", nullptr));
        Add_State_Button->setText(QApplication::translate("VennomUI", "New State", nullptr));
        End_State_Button->setText(QApplication::translate("VennomUI", "End Current State", nullptr));
        iDelete_Button->setText(QApplication::translate("VennomUI", "Delete ", nullptr));
        Add_Param_Button->setText(QApplication::translate("VennomUI", "New Parameter", nullptr));
        Add_Dep_Button->setText(QApplication::translate("VennomUI", "Add Dependency", nullptr));
        WriteIonButton->setText(QApplication::translate("VennomUI", "Write to File", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("VennomUI", "Channel Designer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("VennomUI", "Neuron Designer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("VennomUI", "Network Configurator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VennomUI: public Ui_VennomUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENNOMUI_H
