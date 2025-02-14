#include "vennomui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VennomUI w;
    w.show();

    return a.exec();
}
