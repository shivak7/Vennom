#include "vennomui.h"
#include "ui_vennomui.h"
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include<QMessageBox>
#include <QKeyEvent>

VennomUI::VennomUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VennomUI)
{
    ui->setupUi(this);
    //showMaximized();
    ListFiles();
    InitIonTree();

    //cbui = new ClassBrowser;
    //cbui->show();
}

VennomUI::~VennomUI()
{
    //delete cbui;
    delete ui;
}

int VennomUI :: ListFiles()
{
    QDir dir;
    dir.setCurrent("./systems/");
    dir.setNameFilters(QStringList()<<"*.vmdl");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name | QDir::IgnoreCase);

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i)
    {
            QFileInfo fileInfo = list.at(i);

            std::fstream f(fileInfo.absoluteFilePath().toStdString().c_str(),std::ios::in);
            std::string descript;
            f >> descript;
            f.close();
            QString qdescript = QString(descript.c_str());

            ui->listWidget->addItem(qdescript);
            std::cout << descript;
            std::cout << std::endl;
    }

        return 0;
}

void enableEdit(QTreeWidgetItem* pItem)
{
Qt::ItemFlags eFlags = pItem->flags();
eFlags |= Qt::ItemIsEditable;
eFlags |= Qt::ItemIsSelectable;
//Qt::Key_Delete;
pItem->setFlags(eFlags);
}

int VennomUI :: InitIonTree()
{
    ui->ion_tree->setColumnCount(3);

    QString Header1 = "Definition";
    QString Header2 = "Value";
    QString Header3 = "Name/Description";
    QStringList HeaderList;
    HeaderList.push_back(Header1);
    HeaderList.push_back(Header2);
    HeaderList.push_back(Header3);
    ui->ion_tree->setHeaderLabels(HeaderList);
    ui->ion_tree->header()->resizeSection(0,200);
    ui->ion_tree->header()->resizeSection(1,200);

    top0 = new QTreeWidgetItem(ui->ion_tree);
    top0->setText(0,tr("VSYS ION "));

    QTreeWidgetItem *sid = new QTreeWidgetItem(top0);
    sid->setText(0,tr("UID"));
    sid->setText(2,tr("Unique String ID"));
    enableEdit(sid);

    QTreeWidgetItem *cid = new QTreeWidgetItem(top0);
    cid->setText(0,tr("CID"));
    cid->setText(2,tr("Class ID"));
    enableEdit(cid);

    v_items.append(sid);
    v_items.append(cid);

    ui->ion_tree->expandAll();

    class_box->addItem("4");                                        //adds selections for comboboxes
    class_box->addItem("5");
    class_box->addItem("6");
    class_box->addItem("7");
    class_box->addItem("8");
    class_box->addItem("9");
    ui->ion_tree->setItemWidget(cid,1,class_box);

    ui->ion_tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    curr_item = top0;
    return 0;
}

void VennomUI::keyPressEvent(QKeyEvent *e)
{

          QMessageBox* box = new QMessageBox();
          if(e->key()==Qt::Key_Delete)
            on_iDelete_Button_clicked();

          //ui->ion_tree->focusWidget()

};

void VennomUI::on_ion_tree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{

    if(item->text(0)=="state")
    {
        if(column==2)
        {
            item->text(column) = "";
            ui->ion_tree->editItem(item,column);
        }
     }
    else
    {
        if((column==1)||(column==2))
        ui->ion_tree->editItem(item,column);
    }

}

void VennomUI::on_WriteIonButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                           tr("Save Xml"), ".",
                                           tr("Xml files (*.xml)"));

    if(filename.isEmpty())
        return;

    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("vsys");
    xmlWriter.writeAttribute("type","hh_ion");

     QTreeWidgetItem * t_ptr;
     t_ptr = ui->ion_tree->topLevelItem(0);

     std::cout << "Toplevel count: " << ui->ion_tree->topLevelItemCount() << std::endl;

     if(t_ptr->childCount() >= 2)
     {
        QString sid = t_ptr->child(0)->text(1);
        QString cid = class_box->currentText();//t_ptr->child(1)->text(1);

            xmlWriter.writeTextElement("sid",sid);
            xmlWriter.writeTextElement("cid",cid);

        curr_item = t_ptr->child(2);
        std::cout << "Child 2: " << curr_item->text(0).toStdString() << std::endl;

        while(curr_item!=NULL)
        {
            QTreeWidgetItem * next_item;

            if(curr_item->text(0).toStdString()=="parameter")
            {
                QString param = curr_item->text(1);
                QString param_name = curr_item->text(2);
                xmlWriter.writeStartElement("parameter");
                xmlWriter.writeAttribute("name",param_name);
                xmlWriter.writeTextElement("value",param);
                xmlWriter.writeEndElement();

                int cpos = curr_item->parent()->indexOfChild(curr_item);
                std::cout << "Current pos: " << cpos << std::endl;
                if(cpos<curr_item->parent()->childCount())
                    next_item = curr_item->parent()->child(cpos+1);
                else
                    next_item = NULL;
            }
            else if(curr_item->text(0)=="state")        //Absolutely no nested states allowed
            {
                std:: cout << "State item " << std::endl;
                QString state_name = curr_item->text(2);

                if(state_name=="Enter State Name Here")
                    state_name = "";

                xmlWriter.writeStartElement("state");
                xmlWriter.writeAttribute("name",state_name);

                if(curr_item->childCount()>=1)
                    next_item = curr_item->child(0);
                else
                    next_item = NULL;

            }
            else if(curr_item->text(0)=="IntegrationFlag")        //Absolutely no nested states allowed
            {
                std:: cout << "IntFlag item " << std::endl;
                QComboBox* box = qobject_cast<QComboBox*>(ui->ion_tree->itemWidget(curr_item, 1));
                QString Int_Flag = box->currentText();

                xmlWriter.writeTextElement("IntegrationFlag", Int_Flag);

                int cpos = curr_item->parent()->indexOfChild(curr_item);
                std::cout << "Current pos: " << cpos << std::endl;
                if(cpos<curr_item->parent()->childCount())
                    next_item = curr_item->parent()->child(cpos+1);
                else
                    next_item = NULL;
            }
            else if(curr_item->text(0)=="dependency")        //Absolutely no nested states allowed
            {
                QString Dep_type = curr_item->text(2);
                QString Dep_val = curr_item->text(1);
                xmlWriter.writeStartElement("dependency");
                xmlWriter.writeAttribute("type",Dep_type);
                xmlWriter.writeTextElement("value",Dep_val);
                xmlWriter.writeEndElement();

                int cpos = curr_item->parent()->indexOfChild(curr_item);
                //std::cout << "Current pos: " << cpos << std::endl;
                if(cpos<curr_item->parent()->childCount())
                    next_item = curr_item->parent()->child(cpos+1);
                else
                    next_item = NULL;
            }

            if(next_item==NULL)
            {
                if(curr_item->parent()!=top0)
                {
                  xmlWriter.writeEndElement();
                  curr_item = curr_item->parent();
                  int cpos = curr_item->parent()->indexOfChild(curr_item);
                  if(cpos<curr_item->parent()->childCount())
                      next_item = curr_item->parent()->child(cpos+1);
                  else
                      next_item = NULL;
                }
            }

            curr_item = next_item;
        }

     }

    curr_item = top0->child(top0->childCount()-1);  //Point to last main child
    xmlWriter.writeEndElement();
    file.close();

}

void VennomUI::on_Add_State_Button_clicked()
{
    if(curr_item!=top0)
        curr_item = top0;

        QTreeWidgetItem *item = new QTreeWidgetItem(curr_item);
        item->setText(0,tr("state"));
        item->setText(1,tr("------"));
        item->setText(2,"Enter State Name Here");
        enableEdit(item);

        item = new QTreeWidgetItem(item);
        item->setText(0,tr("IntegrationFlag"));
        enableEdit(item);
        curr_item = item->parent();
//        curr_item = item;

        QComboBox *box = new QComboBox();
        box->addItem("1");
        box->addItem("2");
        box->addItem("3");

        ui->ion_tree->setItemWidget(item, 1, box);

        ui->ion_tree->expandAll();



}

void VennomUI::on_Add_Param_Button_clicked()
{
    //if((curr_item->text(0)!="parameter")&&(curr_item->text(0)!="dependency")&&(curr_item->text(0)!="UID")&&(curr_item->text(0)!="CID"));
    //else curr_item = curr_item->parent();
    if((curr_item->text(0)!="state")&&(curr_item!=top0))
    curr_item = curr_item->parent();


        QTreeWidgetItem *item = new QTreeWidgetItem(curr_item);
        item->setText(0,tr("parameter"));
        enableEdit(item);
        ui->ion_tree->expandAll();

}

void VennomUI::on_ion_tree_itemClicked(QTreeWidgetItem *item, int column)
{
    //if(item->parent()!=NULL)    //If not root
    //    curr_item = item->parent(); //Point to parent
    //else
        curr_item = item;   //If root, then point to root's child
    //ui->ion_tree->setCurrentItem(item);

       // std::cout << "Click detected!" << std::endl;
}

void VennomUI::on_End_State_Button_clicked()
{
    if(curr_item!=top0)
    curr_item = curr_item->parent();
}

void VennomUI::on_iDelete_Button_clicked()
{
    std::cout << curr_item->text(0).toStdString() << std::endl;

    if((curr_item!=NULL)&&(curr_item!=top0)&&(top0->childCount()>2)&&(curr_item->text(0)!="UID")&&(curr_item->text(0)!="CID")&&(curr_item->text(0)!="IntegrationFlag"))
    {
        QTreeWidgetItem * p = curr_item->parent();
        int cpos = curr_item->parent()->indexOfChild(curr_item)-1;
        p->removeChild(curr_item);

        if((cpos+1 < p->childCount())&&(cpos>=0))
            curr_item = p->child(cpos+1);
        else
        {
            if(p->child(cpos)!=NULL)
                curr_item = p->child(cpos);
            else
                curr_item = p;
        }

    }
}

void VennomUI::DependBrowse()
{
    depfile_selected = QFileDialog::getOpenFileName(this,tr("Open VMDL file"),"./",tr("VMDL Files *.vmdl"));
    QFileInfo Finfo(depfile_selected);
    QObject *button = sender();
    QTreeWidgetItem* item  = map.value(button);
    item->setText(1,Finfo.fileName());

}

void VennomUI::on_Add_Dep_Button_clicked()
{
    if(curr_item!=top0)
        curr_item = top0;

        QTreeWidgetItem *item = new QTreeWidgetItem(curr_item);
        item->setText(0,tr("dependency"));
        enableEdit(item);
        curr_item = item; //was item->Parent()

        QPushButton *browse = new QPushButton();
        browse->setText("Browse");
        QObject::connect(browse,SIGNAL(clicked(bool)),this,SLOT(DependBrowse()));
        ui->ion_tree->setItemWidget(item, 2, browse);
        map.insert(browse, item);

}

void VennomUI::on_ion_tree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    curr_item = current;
}
