#include "fileattrwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileAttrWidget w;
    w.show();

    return a.exec();
}
