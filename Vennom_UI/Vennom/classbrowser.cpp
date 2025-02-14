#include "classbrowser.h"
#include "ui_classbrowser.h"

ClassBrowser::ClassBrowser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClassBrowser)
{
    ui->setupUi(this);
}

ClassBrowser::~ClassBrowser()
{
    delete ui;
}
