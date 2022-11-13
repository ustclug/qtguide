#include "imagetransformwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageTransformWidget w;
    w.show();

    return a.exec();
}
