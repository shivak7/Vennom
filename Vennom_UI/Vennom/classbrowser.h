#ifndef CLASSBROWSER_H
#define CLASSBROWSER_H

#include <QMainWindow>

namespace Ui {
class ClassBrowser;
}

class ClassBrowser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClassBrowser(QWidget *parent = 0);
    ~ClassBrowser();

private:
    Ui::ClassBrowser *ui;
};

#endif // CLASSBROWSER_H
