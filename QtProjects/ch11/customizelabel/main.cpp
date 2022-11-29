#include "widgetcustomizelabel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetCustomizeLabel w;
    w.show();

    return a.exec();
}
