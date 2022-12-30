#include "widgetcalcmd5.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetCalcMD5 w;
    w.show();

    return a.exec();
}
