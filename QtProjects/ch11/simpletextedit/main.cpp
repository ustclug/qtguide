#include "widgetsimpletextedit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetSimpleTextEdit w;
    w.show();

    return a.exec();
}
