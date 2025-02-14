#ifndef VENNOMUI_H
#define VENNOMUI_H

#include <QMainWindow>
#include <QDir>
#include <iostream>
#include <fstream>
#include <string>
#include <QtWidgets/QTreeWidget>
#include "classbrowser.h"
#include <QComboBox>

namespace Ui {
class VennomUI;
}

class VennomUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit VennomUI(QWidget *parent = 0);
    ~VennomUI();

private slots:

    void DependBrowse();

    void on_ion_tree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_WriteIonButton_clicked();

    void on_Add_State_Button_clicked();

    void on_Add_Param_Button_clicked();

    void on_ion_tree_itemClicked(QTreeWidgetItem *item, int column);

    void on_End_State_Button_clicked();

    void on_iDelete_Button_clicked();

    void on_Add_Dep_Button_clicked();

    void keyPressEvent(QKeyEvent * event);

    void on_ion_tree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    ClassBrowser *cbui;
    Ui::VennomUI *ui;
    QTreeWidgetItem *top0;
    QComboBox *class_box = new QComboBox();
    QTreeWidgetItem *curr_item;
    QList<QTreeWidgetItem *> v_items;
    QMap<QObject *, QTreeWidgetItem *> map;
    QString depfile_selected;
    int ListFiles();
    int InitIonTree();
};

#endif // VENNOMUI_H
